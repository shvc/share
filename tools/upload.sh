#!/bin/sh
#
#
print_usage()
{
    local base_name=$(basename $0)
    echo -e "\033[0;31m Usage: \033[0m $base_name [options...]"
    echo -e " -h host  Host address(default 127.0.0.1)"
    echo -e " -p port  port(default 3000)"
    echo -e " -k key   Object key(default random num)"
    echo -e " -f file  filename"
    echo -e " -o options  curl options"
    exit 1
}

host=127.0.0.1
port=3000
eval $(awk 'BEGIN{srand(); printf("random=%05d",rand()*100000)}')
key="key-$random"
filename=tmp.dat
options='-s'

while getopts ':h:p:k:f:o:' opt
do
    case $opt in
    h) host=$OPTARG
    ;;
    p) port="${OPTARG}"
    ;;
    k) key=$OPTARG
    ;;
    f) filename=$OPTARG
    ;;
    o) options="-$OPTARG"
    ;;
    ?) echo '  error'
       print_usage
    ;;
    esac
done

eval $(curl ${options} -XPOST "http://${host}:${port}/token?entryKey=$key&entryOp=put" | awk -F\" '{printf("token=%s\n",$4)}')
curl ${options} -XPOST "http://${host}:${port}/pblocks/$key?token=$token" -H "Content-Type: application/octet-stream" --data-binary @$filename
echo "key: $key token: $token file:$filename"

