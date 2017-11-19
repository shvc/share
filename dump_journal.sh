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
	echo "id: $chunkid" > /dev/null
	mkdir -p $chunkid
	curl -s "http://${ipaddr}:9101/diagnostic/1/ShowChunkInfo?cos=${cos}&chunkid=${chunkid}" > $chunkid/${chunkid}.info
	# get chunk primary vdc(zone)
	zone=$(awk '/primary:/{print $2}' $chunkid/${chunkid}.info)
	# get sealed time
	sealedTime=$(awk '/sealedTime:/{print $2}' $chunkid/${chunkid}.info)
	# get chunk dtId
	curl -s "http://${ipaddr}:9101/diagnostic/CT/1/DumpAllKeys/CHUNK?chunkId=${chunkid}&useStyle=raw" | grep -B1 schema > $chunkid/${chunkid}.dtId
	dtId=$(awk '/http/{print $4}' $chunkid/${chunkid}.dtId)
	# List JR(Journal Region)
	curl -s "http://${ipaddr}:9101/diagnostic/PR/2/DumpAllKeys/DIRECTORYTABLE_RECORD?type=JOURNAL_REGION&dtId=${dtId}&zone=${zone}&useStyle=raw&showvalue=gpb" | grep -B1 schema > $chunkid/${chunkid}.JR
	# Dump JR content
	curl -s "http://ip:9101/journalcontent/${dtId}?zone=${zone}&major=xxx&minor=xxx" > $chunkid/${chunkid}.JRContent
done < $chunkidfile

