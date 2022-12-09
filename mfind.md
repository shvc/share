## muti-threads find
```
#!/bin/sh

srcfile="/tmp/find.$$"
dstdir="/tmp/MFindOut"
rm -rf $dstdir/*

# specify mtime YYMMDDhhmm.ss
touch -m -t 201907261505.09 /opt/.timefile

find /baodan/EPDownload/ -maxdepth 1 -mindepth 1 -type d > $srcfile

echo $srcfile
echo $dstdir

xargs -a $srcfile -I NODE -P0 sh -c 'find NODE -type f -newer /opt/.timefile > /tmp/FindOut/out.$$'
```
