# docker proxy
```
# command line arg
docker build --build-arg http_proxy=http://10.239.4.80:913 --build-arg https_proxy=http://10.239.4.80:913 .

# Dockerfile
ENV http_proxy 10.239.4.80:913
```
