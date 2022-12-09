## cosbench
https://github.com/open-io/cosbench

#### parse cosbench result
```awk
awk -F, '{if($1=="read"){
      rop+=$3;rbyte+=$4;rres+=$5;rpoc+=$6;rt+=$7;rcnt++
    }else if($1=="write"){
      wop+=$3;wbyte+=$4;wres+=$5;wpoc+=$6;wt+=$7;wcnt++
    }}
    END{
      printf("read : %d, %d, %.2f, %.2f, %.2f\n",rop,rbyte/1000,rres/rcnt,rpoc/rcnt,rt);
      printf("write: %d, %d, %.2f, %.2f, %.2f\n",wop,wbyte/1000,wres/wcnt,wpoc/wcnt,wt)
    }' archive/w2-s3-minio-2n-2d/s3-main-worker.csv
```

### fio
```
fio -name=randread -direct=1 -iodepth=64 -rw=randread -ioengine=libaio -bs=4k -size=4G -numjobs=1 -runtime=1000 -group_reporting -filename=/dev/sdc

fio -name=randwrite -direct=1 -iodepth=64 -rw=randwrite -ioengine=libaio -bs=4k -size=4G -numjobs=1 -runtime=1000 -group_reporting -filename=/dev/sdc

fio -name=read -direct=1 -iodepth=64 -rw=read -ioengine=libaio -bs=4k -size=4G -numjobs=1 -runtime=1000 -group_reporting -filename=/dev/sdc

fio -name=write -direct=1 -iodepth=64 -rw=write -ioengine=libaio -bs=4k -size=4G -numjobs=1 -runtime=1000 -group_reporting -filename=/dev/sdc
```
