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
cos=`curl -s "http://${ipaddr}:9101/stats/ssm/varraycapacity/" | awk -F'[<>]' '/VarrayId/{print $3}'`
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

while read chunkid
do
	echo "id: $chunkid"
done < $chunkidfile

