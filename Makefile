
.PHONY: all
all: readline copy sort

readline: readline.c
	$(CC) -o $@ $<

copy: copy.c
	$(CC) -o $@ $<

sort: sort.c
	$(CC) -o $@ $<
