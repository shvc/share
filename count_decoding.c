#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * A message containing letters fromA-Zis being encoded to digitsbers using the following mapping:
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * Given an encoded message containing digits, determine the total digitsber of ways to decode it.
 * For example,
 * Given encoded message"12",it could be decoded as"AB"(1 2) or"L"(12).
 * The digitsber of ways decoding"12"is 2.
 *
 * http://www.geeksforgeeks.org/count-possible-decodings-given-digit-sequence
 *
 */

int char2int(char c)
{
	int ret = 0;
	if(c >= 'A' && c <= 'Z') {
		ret = c - 'A' + 1;
	}
	return ret;
}

int count_decoding(char* digits, size_t n)
{
}

int dp_count_decoding(char* digits, size_t len)
{
	int i, ret = 0;
	int *p = NULL;

	if(NULL == digits || digits[0] == '0' || len == 0) {
		return 0;
	}
	if(len == 1) {
		if(digits[0] == '0') {
			return 0;
		}
		else {
			return 1;
		}
	}
	p = malloc(len);
	p[0] = 1;
	p[1] = (digits[1]=='0'?0:1) + (char2int(digits[0]) * 10 + char2int(digits[1])?1:0);
	for(i=2; i<len; i++) {
		if( digits[i] != '0') {
			p[i] += p[i-1];
		}
		if( digits[i-1] != '0' && (char2int(digits[i-1]) * 10 + char2int(digits[i])?1:0) ) {
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

	printf("%s, sn: %d\n", "1", count_decoding("1", 1));
	printf("%s, sn: %d\n", "11", count_decoding("11", 2));
	printf("%s, sn: %d\n", "111", count_decoding("111", 3));
	printf("%s, sn: %d\n", array, count_decoding(array, len));

	return 0;
}

