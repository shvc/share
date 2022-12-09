- iptables add src ip restriction
```
Host network:
iptables -I INPUT -p tcp ! -i lo --dport 6380 -j DROP
iptables -I INPUT -p tcp --dport 6380 -s 10.0.0.1,10.0.0.2,10.0.0.3 -j RETURN

docker network:
iptables -I DOCKER-USER -p tcp ! -i lo --dport 6380 -j DROP
iptables -I DOCKER-USER -p tcp --dport 6380 -s 10.0.0.1,10.0.0.2,10.0.0.3 -j RETURN
iptables -I DOCKER-USER -i lo -j RETURN
```

- firewalld
