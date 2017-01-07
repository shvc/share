#include <stdio.h>

/* solution 1 */
int odd_times_num1(int *a, size_t len)
{
	int i, j, cnt;

	for(i=0; i<len; i++) {
		cnt = 1;
		for(j=0; j<len; j++) {
			if(i == j) continue;
			if(a[i] == a[j]){
				cnt++;
			}
		}
		if(cnt%2) break;
	}
	return a[i];
}

/* solution 2 */
int odd_times_num2(int *a, size_t len)
{
	int i, x = 0;
	
	for(i=0; i<len; i++) {
		x = x^a[i];
	}

	return x;
}

int main(int argc, char** argv)
{
	int ret = 0;
	int i   = 0;
	int len = 0;
	int a[]={-1, 0, 1, -1, 0, 1, 3, 4, 3, 4, 1};
	
	len = sizeof(a)/sizeof(int);
	for(i=0; i<len; i++){
		printf("%2d ", a[i]);
	}
	printf("\n");

	printf("odd times num: %i\n", odd_times_num1(a, len));
	printf("odd times num: %i\n", odd_times_num2(a, len));
	return ret;
}

