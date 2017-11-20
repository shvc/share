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

cos=`curl -s "http://${ipaddr}:9101/stats/ssm/varraycapacity/" | awk -F'[<>]' '/VarrayId/{print $3}'`

while read chunkid
do
	echo "chunkid: $chunkid"
	mkdir -p $chunkid
	curl -s "http://${ipaddr}:9101/diagnostic/1/ShowChunkInfo?cos=${cos}&chunkid=${chunkid}" > $chunkid/${chunkid}.info
	# get chunk primary(zone) and sealedTime
	eval $(awk '/primary/{printf "zone=\047%s\047\n",$2};/sealedTime:/{printf "sealedTime=\047%s\047\n",$2}' $chunkid/${chunkid}.info)
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
	curl -s "$jr_url" > $chunkid/${chunkid}.JRDetail
	eval $(awk -v sealedTime=$sealedTime '$1 ~ /schemaType/{major=$10} $1 ~ /timestamp:/{if(0 < $2 - sealedTime) {printf "major=%s;timestamp=%s\n",major,$2;exit}}' CT_78_JR)
	echo "major: $major"
	echo "timestamp: $timestamp"
	# Dump JR content
	curl -s "http://ip:9101/journalcontent/${dtId}?zone=${zone}&major=$major" > $chunkid/${chunkid}.JRContent${major}
done < $chunkidfile

