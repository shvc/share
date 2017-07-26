#include <stdio.h>

int reverse(int x)
{
	int y = 0;
	while(x) {
		y = y*10 + x%10;
		x /= 10;
	}	
	return y;
}


int reversDigits(int x)
{
	int num = x>0?x:-x; 
	int prev_rev_num = 0, rev_num = 0, curr_digit;
	while (num != 0)
	{
		curr_digit = num%10;

		rev_num = (rev_num*10) + curr_digit;

		if ((rev_num - curr_digit)/10 != prev_rev_num)
		{
			/* overflow */
			return 0;
		}

		prev_rev_num = rev_num;
		num = num/10;
	}

	return x>0? rev_num : -rev_num;
}

int main(int argc, char** argv)
{
	int x = 123;
	printf("sizeof(int)   = %d\n", sizeof(int));
	printf("sizeof(short) = %d\n", sizeof(short));
	printf("%d, %d\n", x, reverse(x));

	x = -123;
	printf("%d, %d\n", x, reverse(x));

	x = -123456789;
	printf("%d, %d\n", x, reverse(x));

	return 0;
}

