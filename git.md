
## git config
base  
```
git config --global alias.b branch
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.cm commit
git config --global alias.pr pull --rebase
git config --global alias.pf push --force
git config --global alias.ll log --oneline
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
# git proxy
git config --global http.proxy http://192.168.1.1:1080
git config --global http.https://golang.org.proxy socks5://192.168.1.1:1080
# or
git config --global http.proxy socks5://192.168.1.1:1080
git config --global http.proxy socks5h://192.168.1.1:1080

# bash proxy
export http_proxy=socks5h://172.16.3.235:1888
export HTTPS_PROXY=socks5h://172.16.3.235:1888
export ALL_PROXY=socks5h://172.16.3.235:1888
```

create a tag and push
```
git tag -a v1.0.0 -m 'version 1.0.0' bffd78b
git push origin v1.0.0
```

delete tag  
```
git tag -d tagName
git push origin :refs/tags/tagName
```

checkout tag to branch
```
git checkout tags/v3.2.7 -b v3.2.7
```

remote
```
# add a remote: upstream
git remote add upstream https://github.com/minio/minio.git
# set current default remote to upstream
git branch --set-upstream-to upstream
```

rebase
```
git pull --rebase upstream main
git rebase -i bffd78b
git push -f
```
