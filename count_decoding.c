#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * A message containing letters fromA-Zis being encoded to strbers using the following mapping:
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * Given an encoded message containing str, determine the total strber of ways to decode it.
 * For example,
 * Given encoded message"12",it could be decoded as"AB"(1 2) or"L"(12).
 * The strber of ways decoding"12"is 2.
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

int recursive_count_decoding(char* str, size_t n)
{
	int count = 0;

	if( n == 0 || n == 1) {
		return 1;
	}

	if( str[n-1] > '0') {
		count = recursive_count_decoding(str, n-1);
	}

	if( str[n-2] == '1' || (str[n-2]=='2' && str[n-1] < '7')) {
		count += recursive_count_decoding(str, n-2);
	}

	return count;
}

int dp_count_decoding(char* str, size_t len)
{
	int i, ret = 0;
	int *pc = NULL;

	if(NULL == str || str[0] == '0' || len == 0) {
		return 0;
	}

	pc = malloc(sizeof(int) *(len + 1));
	pc[0] = 1;
	pc[1] = 1;
	for(i=2; i<=len; i++) {
		pc[i] = 0;
		if( str[i-1] > '0') {
			pc[i] = pc[i-1];
		}
		if( str[i-2] == '1' || (str[i-2] == '2' && str[i-1] < '7') ) {
			pc[i] += pc[i-2];
		}
	}
	ret = pc[len];
	free(pc);
	return ret;
}

int main(int argc, char** argv)
{
	char array[] = "131235";
	size_t len = strlen(array);
	int (*func)(char*, size_t);
	func = dp_count_decoding;
	//func = recursive_count_decoding;

	printf("char 0: ansi: %d\n", '0');
	printf("char A: ansi: %d\n", 'A');
	printf("char a: ansi: %d\n", 'a');
	printf("key  A: value: %d\n", char2int('A'));
	printf("key  B: value: %d\n", char2int('B'));
	printf("key  Z: value: %d\n", char2int('Z'));

	printf("%8s, sn: %d\n", "1", func("1", 1));
	printf("%8s, sn: %d\n", "11", func("11", 2));
	printf("%8s, sn: %d\n", "111", func("111", 3));
	printf("%8s, sn: %d\n", "1234", func("1234", 4));
	printf("%8s, sn: %d\n", "1230", func("1230", 4));
	printf("%8s, sn: %d\n", "10000", func("10000", 5));
	printf("%8s, sn: %d\n", "10023", func("10023", 5));
	printf("%8s, sn: %d\n", array, func(array, len));

	return 0;
}

