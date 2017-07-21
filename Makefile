#
# date: Fri Jul 21 23:34:36 CST 2017
#


binarys := $(patsubst %.c, %, $(wildcard *.c))

.PHONY: all
all: $(binarys)

%: %.c
	$(CC) -o $@ $<

.PHONY: clean
clean:
	rm -f $(binarys)
