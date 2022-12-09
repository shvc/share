
all:valid setaddr
valid: valid.c common.c
	cc -o valid valid.c common.c
setaddr: setaddr.c
	cc -o setaddr setaddr.c common.c
clean:
	rm -f *.o valid setaddr
