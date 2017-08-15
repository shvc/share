#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * A message containing letters fromA-Zis being encoded to numbers using the following mapping:
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * Given an encoded message containing digits, determine the total number of ways to decode it.
 * For example,
 * Given encoded message"12",it could be decoded as"AB"(1 2) or"L"(12).
 * The number of ways decoding"12"is 2.
 */

int char2int(char c)
{
	int ret = 0;
	if(c >= 'A' && c <= 'Z') {
		ret = c - 'A' + 1;
	}
	return ret;
}

int num_decoding(char* num, size_t len)
{
	int i, ret = 0;
	int *p = NULL;

	if(NULL == num || num[0] == '0' || len == 0) {
		return 0;
	}
	if(len == 1) {
		if(num[0] == '0') {
			return 0;
		}
		else {
			return 1;
		}
	}
	p = malloc(len);
	p[0] = 1;
	p[1] = (num[1]=='0'?0:1) + (char2int(num[0]) * 10 + char2int(num[1])?1:0);
	for(i=2; i<len; i++) {
		if( num[i] != '0') {
			p[i] += p[i-1];
		}
		if( num[i-1] != '0' && (char2int(num[i-1]) * 10 + char2int(num[i])?1:0) ) {
			p[i] += p[i-2];
		}
	}
	ret = p[len-1];
	free(p);
	return ret;
}

int main(int argc, char** argv)
{
	char array[] = "131235";
	size_t len = strlen(array);

	printf("char 0: ansi: %d\n", '0');
	printf("char A: ansi: %d\n", 'A');
	printf("char a: ansi: %d\n", 'a');
	printf("key  A: value: %d\n", char2int('A'));
	printf("key  B: value: %d\n", char2int('B'));
	printf("key  Z: value: %d\n", char2int('Z'));

	printf("%s, sn: %d\n", "1", num_decoding("1", 1));
	printf("%s, sn: %d\n", "11", num_decoding("11", 2));
	printf("%s, sn: %d\n", "111", num_decoding("111", 3));
	printf("%s, sn: %d\n", array, num_decoding(array, len));

	return 0;
}

