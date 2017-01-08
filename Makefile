
.PHONY: all
all: readline copy

readline: readline.c
	$(CC) -o $@ $<

copy: copy.c
	$(CC) -o $@ $<
