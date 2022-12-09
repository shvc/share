mkdir -p /usr/local/share/fonts

cp msyh.ttf /usr/local/share/fonts/
cp simsun.ttf /usr/local/share/fonts/

fc-list :lang=zh

fc-cache -frsv
