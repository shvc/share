#!/bin/sh

print_usage()
{
    echo "$0:"
    echo " -f chunkid file"
    echo " -h host ip address"
    echo " -v verbos"
    exit 1
}

ipaddr=$(hostname -i)
chunkidfile='chunkid.list'

if [ $# -lt 1 ]
then
    print_usage
fi

while getopts ':f:h:v' opt
do
    case $opt in
    f) chunkidfile=$OPTARG
    ;;
    h) ipaddr=$OPTARG
    ;;
    v)
    echo "ip      :$ipaddr"
    echo "chunks  :$chunkids"
    ;;
    ?) echo 'error'
       print_usage
    ;;
    esac
done

if [ ! -e "$chunkidfile" ]
then
    echo "$chunkidfile not exist"
    print_usage
fi

eval $(curl -s "http://${ipaddr}:9101/stats/ssm/varraycapacity/" | awk -F'[<>]' '/VarrayId/{printf "cos=\047%s\047\n",$3}')
if [ "x${cos}" == "x" ]
then
    echo "can not get cos of ${ipaddr}"
    print_usage
fi

# map public ip to private ip to use viprexec
declare -A ipmap=()
eval $(getrackinfo | awk 'NF==8{printf "ipmap[\"%s\"]=%s\n",$5, $1}')
#echo ${ipmap[$public_ip]}

while read -u 99 chunkid
do
    echo "chunkid: $chunkid"
    mkdir -p $chunkid
    curl -s "http://${ipaddr}:9101/diagnostic/1/ShowChunkInfo?cos=${cos}&chunkid=${chunkid}" > $chunkid/${chunkid}.info
    # get chunk primary(zone) and sealedTime
    eval $(awk '/primary/{printf "zone=%s;",$2};/sealedTime:/{printf "sealedTime=\047%s\047\n",$2}' $chunkid/${chunkid}.info)
    echo "zone: $zone"
    echo "sealedTime: $sealedTime"
    # get chunk dtId
    curl -s "http://${ipaddr}:9101/diagnostic/CT/1/DumpAllKeys/CHUNK?chunkId=${chunkid}&useStyle=raw" | grep -B1 schemaType > $chunkid/${chunkid}.dtId
    eval $(awk -F/ '/http/{printf "dtId=\047%s\047\n",$4}' $chunkid/${chunkid}.dtId)
    echo "dtId: $dtId"
    # List JR(Journal Region)
    curl -s "http://${ipaddr}:9101/diagnostic/PR/2/DumpAllKeys/DIRECTORYTABLE_RECORD?type=JOURNAL_REGION&dtId=${dtId}&zone=${zone}&useStyle=raw&showvalue=gpb" | grep -B1 schemaType > $chunkid/${chunkid}.JR
    # get JR url
    eval $(awk 'NR==1 && /http/{printf "jr_url=\047%s\047\n",$0}' $chunkid/${chunkid}.JR)
    echo "JR_URL: $jr_url"
    curl -s "${jr_url%$'\r'}" > $chunkid/${chunkid}.JRDetail
    for ((timeval=sealedTime-800000000; timeval<=sealedTime+400000000; timeval+=200000000))
    do
        eval $(awk -v sealedTime=$timeval '$1 ~ /schemaType/{major=$10} $1 ~ /timestamp:/{if(0 < $2 - sealedTime + 600000000) {printf "major=%s;timestamp=%s\n",major,$2;exit}}' $chunkid/${chunkid}.JRDetail)
        # Dump JR content
        if [ "x$major" != "x" ]
        then
            curl -s "http://${ipaddr}:9101/journalcontent/${dtId}?zone=${zone}&major=$major" > $chunkid/${chunkid}.JRContent.${major}
            if grep $chunkid $chunkid/${chunkid}.JRContent.${major} > /dev/null
            then
                echo "major: $major"
                echo "timestamp: $timestamp"
                awk -v chunkid="$chunkid" -v zone="$zone" 'BEGIN{flag=0}/schemaType CHUNK chunkId/,/capacity:/{if($1=="<schemaKey>schemaType" && $2=="CHUNK" && $4 ~ chunkid){flag=1}else if($1=="<schemaKey>schemaType" && $2=="CHUNK" && $4 !~ chunkid){if(flag==1){flag=0;exit}else{flag=0}}if(flag){print}}' $chunkid/${chunkid}.JRContent.${major} > $chunkid/${chunkid}.JRContent.${major}.result
                startline=0
                for ((i=1; i<=2; i++))
                do
                    echo "startline   : $startline"
                    eval $(awk -v startline=$startline 'BEGIN{flag=1}NR>=startline{if($1~"ssId"){printf "ssId=%s;",$2}else if($1~"partitionId"){printf "partitionId=%s;",$2}else if($1~"filename"){printf "filename=%s;",$2}else if($1~"offset"&&flag){flag=0;printf "offset=%s;",$2}else if($1~"endOffset"){printf "startline=%s\n",NR+3; exit}}' $chunkid/${chunkid}.JRContent.${major}.result)

                    echo "ssId        : $ssId"
                    echo "partitionId : $partitionId"
                    echo "filename    : $filename"
                    echo "offset      : $offset"
                    echo "endOffset   : $endOffset"
                    echo viprexec -n ${ipmap[$ssId]} --dock=object-main \'"dd if=/dae/uuid-${partitionId}/${filename} of=/var/log/${chunkid}.copy${i} bs=1 skip=${offset} count=${endOffset}"\'
                    viprexec -n ${ipmap[$ssId]} --dock=object-main \'"dd if=/dae/uuid-${partitionId}/${filename} of=/var/log/${chunkid}.copy${i} bs=1 skip=${offset} count=${endOffset}"\'
                    echo scp ${ipmap[$ssId]}:/opt/emc/caspian/fabric/agent/services/object/main/log/${chunkid}.copy${i} ${chunkid}/${chunkid}.copy${i}
                    scp ${ipmap[$ssId]}:/opt/emc/caspian/fabric/agent/services/object/main/log/${chunkid}.copy${i} ${chunkid}/${chunkid}.copy${i}
                done
                # break for loop
                break
            else
                rm -f $chunkid/${chunkid}.JRContent.${major}
            fi
        else
            echo "major not find"
        fi
    done
    echo "--  ----------------------------  --"
done 99< $chunkidfile

