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
	return 0;
}

int dp_count_decoding(char* digits, size_t len)
{
	int i, ret = 0;
	int *count = NULL;

	if(NULL == digits || digits[0] == '0' || len == 0) {
		return 0;
	}
	if(len == 1 && digits[0] == '0' ) {
		return 0;
	}

	count = malloc(sizeof(int) *(len + 1));
	count[0] = 1;
	count[1] = 1;
	for(i=2; i<=len; i++) {
		count[i] = 0;
		if( digits[i-1] > '0') {
			count[i] = count[i-1];
		}
		if( digits[i-2] == '1' || (digits[i-2] == 2 && digits[i-1] < 7) ) {
			count[i] += count[i-2];
		}
	}
	ret = count[len];
	free(count);
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

	printf("%s, sn: %d\n", "1", dp_count_decoding("1", 1));
	printf("%s, sn: %d\n", "11", dp_count_decoding("11", 2));
	printf("%s, sn: %d\n", "111", dp_count_decoding("111", 3));
	printf("%s, sn: %d\n", "1234", dp_count_decoding("1234", 4));
	printf("%s, sn: %d\n", array, dp_count_decoding(array, len));

	return 0;
}

