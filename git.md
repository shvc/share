
## git config
base  
```
git config --global alias.b branch
git config --global alias.st status
git config --global alias.co checkout
git config --global credential.helper cache
git config --global color.ui auto
git config --global core.editor vi
```

reset local branch to remote
```
git fetch origin
git reset --hard origin/master
```

proxy
```
git config --global http.proxy http://192.168.1.1:1080
git config --global http.https://golang.org.proxy socks5://192.168.1.1:1080
```
or  
```
git config --global http.proxy socks5://192.168.1.1:1080
git config --global http.proxy socks5h://192.168.1.1:1080
```

bash env proxy
```
export http_proxy=socks5h://172.16.3.235:1888
export HTTPS_PROXY=socks5h://172.16.3.235:1888
export ALL_PROXY=socks5h://172.16.3.235:1888
```

create a tag and push
```
git tag -a v1.0.0 -m 'version 1.0.0' ff57e5c4d4e96dd52127af2d4abff75f96d889cc

git push origin v1.0.0
```
delete tag  
```
git tag -d tagName
git push origin :refs/tags/tagName
```

checkout tag
```
git checkout tags/v3.2.7 -b v3.2.7
```
