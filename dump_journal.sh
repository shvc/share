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

eval $(curl -s "http://${ipaddr}:9101/stats/ssm/varraycapacity/" | awk -F'[<>]' '/VarrayId/{printf "cos=\047%s\047\n",$3}')
if [ "x${cos}" == "x" ]
then
    echo "can not get cos"
    print_usage
fi

while read chunkid
do
    echo "chunkid: $chunkid"
    mkdir -p $chunkid
    curl -s "http://${ipaddr}:9101/diagnostic/1/ShowChunkInfo?cos=${cos}&chunkid=${chunkid}" > $chunkid/${chunkid}.info
    # get chunk primary(zone) and sealedTime
    eval $(awk '/primary/{printf "zone=%s\n",$2};/sealedTime:/{printf "sealedTime=\047%s\047\n",$2}' $chunkid/${chunkid}.info)
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
                for ((i=1; i<=2; i++))
                do
                    eval $(awk -v startline="$startline" -v chunkid="$chunkid" -v zone="$zone" 'NR<=startline{next} /<schemaKey>schemaType CHUNK/{if(chunkid!=$4)next} /primary:/{if(zone!=$2)next} /isEc:/{if($2!="false")next} /ssId:/{printf "ssId=%s\n",$2} /partitionId:/{printf "partitionId=%s\n",$2} /filename:/{printf "filename=%s\n",$2} /offset:/{printf "offset=%s\n",$2} /endOffset:/{printf "endOffset=%s\nstartline=%s\n",$2,NR;  exit}' $chunkid/${chunkid}.JRContent.${major})
                    
                    echo "ssId        : $ssId"
                    echo "partitionId : $partitionId"
                    echo "filename    : $filename"
                    echo "offset      : $offset"
                    echo "endOffset   : $endOffset"
                    echo viprexec -n "${ssId}" "dd if= of=/tmp/${chunkid}.copy${i} bs=1 skip=${offset} count=${endOffset}"
                    echo scp "${ssId}:/tmp/${chunkid}.copy${i} "
                done
                break
            else
                rm -f $chunkid/${chunkid}.JRContent.${major}
            fi
        
        else
            echo "major not find"
        fi
    done
done < $chunkidfile

