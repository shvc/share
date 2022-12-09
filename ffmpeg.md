## ref
https://www.xiebruce.top/1159.html


## Video
- Thumbnail  
```
ffmpeg -hide_banner -ss 00:01:50.420 -i in.mp4 -s 640x480 -vframes 1 out.jpg
ffmpeg -hide_banner -ss 01:02:35 -i mm-190826.mp4 -vframes 1 out2.jpg
```


- trim and crop(`crop=out_w:out_h:x:y`)
```
ffmpeg -ss 00:01:51 -t 04:57:15 -accurate_seek -i 190815.mp4 -codec copy -avoid_negative_ts 1 out.mp4`

ffmpeg -hwaccel cuda -ss 00:01:51 -t 04:57:15 -i 190815.mp4 -vf crop=410:710:438:10 -c:v h264_nvenc znm-02.mp4

ffmpeg -hwaccel cuda -ss 00:01:51 -t 01:00:40 -i 190826.mp4 -vf crop=410:720:435:00 -c:v h264_nvenc mmm-02.mp4
```
- watermark(delogo=x:y:w:h)
```
ffplay -i znm-190815.mp4 -vf delogo=7:570:186:130:show=1
ffmpeg -i znm-190815.mp4 -vf delogo=7:570:186:130 output.mp3
```

- video to gif(https://github.com/cyburgee/ffmpeg-guide)   
 ```
 笨方式: 
ffmpeg -i cat.mp4 -ss 00:00:02 -t 5 -vf scale=480:-2 cat480.mp4 cat0.mp4
ffmpeg -i cat0.mp4 -r 12 -filter_complex 'drawtext=x=(main_w-text_w)/2:y=main_h-text_h-40:fontfile=assets/msyh.ttc:fontsize=h*0.09:fontcolor=red:text=中' cat01.gif

 好方式(普通品质)
ffmpeg -ss 00:00:02 -t 5 -i cat.mp4 -filter_complex "[0:v] fps=12,scale=w=480:h=-2,drawtext=x=(main_w-text_w)/2:y=main_h-text_h-40:fontfile=assets/msyh.ttc:fontsize=h*0.09:fontcolor=red:text=中" cat03.gif
 好方式(高品质)
ffmpeg -ss 00:00:02 -t 5 -i cat.mp4 -filter_complex "[0:v] fps=12,scale=w=480:h=-2,split [a][b];[a] palettegen=stats_mode=single [p];[b]drawtext=x=(main_w-text_w)/2:y=main_h-text_h-40:fontfile=assets/msyh.ttc:fontsize=h*0.09:fontcolor=red:text=中[t];[t][p] paletteuse=new=1" cat04.gif
 ```

## Image
https://stackoverflow.com/questions/11552565/vertically-or-horizontally-stack-mosaic-several-videos-using-ffmpeg  
ffmpeg -y -i i0.png -i i1.png -i i2.png -i i3.png -filter_complex vstack=inputs=4 io.png  
ffmpeg -i i0.png -i i1.png -i i2.png -filter_complex "[1:v][0:v]scale2ref=iw:ow/mdar[1v][0v];[2:v][0v]scale2ref=iw:ow/mdar[2v][0v];[0v][1v][2v]vstack=3" iov.png  

