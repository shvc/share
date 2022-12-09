#include <stdio.h>
/*
 * https://leetcode.com/problems/reverse-integer/tabs/description
 */

/*
 * not in consideration of integer overflow
 */
int reverse(int x)
{
	int y = 0;
	while(x) {
		y = y*10 + x%10;
		x /= 10;
	}	
	return y;
}


/*
 * in consideration of integer overflow
 */
int reverseDigits(int x)
{
	int rev_num=0, prv_num=0;
	int num = x>0?x:-x;

	while(num) {
		rev_num = rev_num*10 + num%10;
		if( (rev_num-num%10)/10 != prv_num) {
			return 0;
		}
		prv_num = rev_num;
		num /= 10;
	}

	return x>0? rev_num : -rev_num;
}

int main(int argc, char** argv)
{
	int x = 123;
	printf("sizeof(int)   = %d\n", sizeof(int));
	printf("sizeof(short) = %d\n", sizeof(short));
	printf("%d, %d\n", x, reverse(x));
	printf("%d, %d\n", x, reverseDigits(x));

	x = -123;
	printf("%d, %d\n", x, reverse(x));
	printf("%d, %d\n", x, reverseDigits(x));

	x = -123456789;
	printf("%d, %d\n", x, reverse(x));
	printf("%d, %d\n", x, reverseDigits(x));

	return 0;
}

