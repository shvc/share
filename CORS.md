## Chrome test CORS
enter the following code to console
```
var xhr = new XMLHttpRequest();
xhr.open('GET', 'http://192.168.56.3:9000/open/00');
xhr.setRequestHeader('x-access-token', '');
xhr.send();
xhr.onload = function(e) {
    var xhr = e.target;
    console.log(xhr.status);
    console.log(xhr.getResponseHeader('Access-Control-Allow-Origin'));
    console.log(xhr.responseText);
}
```
## curl CORS
#### 1. CORS preflight
```
curl -H 'Origin: http://a.cn' \
 -H 'Access-Control-Request-Method: GET' \
 -H 'Access-Control-Request-Headers: X-Requested-With' \
 -X OPTIONS -v http://127.0.0.1
```

#### 2. CORS GET
```
curl -H 'Origin: http://a.cn' -v http://127.0.0.1
```

## CORS test website
https://www.test-cors.org/

