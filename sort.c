#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void output(int* a, size_t len)
{
	int i;
	for(i=0; i<len; i++) {
		printf("%2i ", a[i]);
	}
	puts("");
	return;
}

void bubble_sort(int* a, size_t len)
{
	int i,j;
	for(i=1; i<len; i++) {
		for(j=0; j<len-i; j++) {
			if(a[j] < a[j+1]) {
				a[j]   = a[j] ^ a[j+1];
				a[j+1] = a[j] ^ a[j+1];
				a[j]   = a[j] ^ a[j+1];
			}
		}
	}
	return ;
}

void optimized_bubble_sort(int* a, size_t len)
{
	int i,j;
	int swapped;
	for(i=1; i<len; i++) {
		swapped = 0;
		for(j=0; j<len-i; j++) {
			if(a[j] < a[j+1]) {
				a[j]   = a[j] ^ a[j+1];
				a[j+1] = a[j] ^ a[j+1];
				a[j]   = a[j] ^ a[j+1];
				swapped = 1;
			}
		}
		if(0 == swapped) {
			break;
		}
	}
	return ;
}

void select_sort(int* a, size_t len)
{
	int i,j;
	for(i=0; i<len-1; i++) {
		for(j=i+1; j<len; j++) {
			if(a[i] > a[j]) {
				a[i] = a[i] ^ a[j];
				a[j] = a[i] ^ a[j];
				a[i] = a[i] ^ a[j];
			}
		}
	}
	return ;
}

void optimized_select_sort(int* a, size_t len)
{
	int i,j;
	int min;
	for(i=0; i<len-1; i++) {
		min = i;
		for(j=i+1; j<len; j++) {
			if(a[min] > a[j]) {
				min = j;
			}
		}
		if(min != i) {
			a[i]   = a[i] ^ a[min];
			a[min] = a[i] ^ a[min];
			a[i]   = a[i] ^ a[min];
		}
	}
	return ;
}

void insert_sort(int* arry, size_t len)
{
	int i,j;
	int temp;

	for(i=1; i<len; i++) {
		temp = arry[i];
		for(j=i-1; j>=0; j--) {
			if(arry[j] > temp) {
				arry[j+1] = arry[j];
			} 
			else {
				break;
			}
		}
		arry[j+1] = temp;
	}

	return ;
}


/* set pivot as low */
void quick_sort_0(int* arry, int low, int high)
{
	int i,j,pivot;
        if( low < high ) {
                i = low;
                j = high;
                pivot = arry[i];
                while( i < j ) {
                        while( arry[j] > pivot && j > i) j--;
			if( i < j)
                        arry[i++] = arry[j];
                        while( arry[i] < pivot && i < j) i++;
			if( i < j)
                        arry[j--] = arry[i];
                }
                arry[i] = pivot;
                quick_sort_0(arry, low, i-1);
                quick_sort_0(arry, j+1, high);
        }
	return ;
}

void quick_sort_1(int* arry, int low, int high)
{
	return ;
}

/* set pivot as high */
void quick_sort_2(int* arry, int low, int high)
{
	int i,j;
	int pivot;
	if ( low < high ) {
		i = low;
		j = high;
		pivot = arry[j];
		while( i<j ) {
			while( i<j && arry[i] < pivot ) i++;
			if( i<j )
			arry[j--] = arry[i];
			while( i<j && arry[j] > pivot ) j--;
			if( i<j )
			arry[i++] = arry[j];
		}
		arry[j] = pivot;
		quick_sort_2(arry, low, i-1);
		quick_sort_2(arry, j+1, high);
	}

}

void quicksort_iterative(int array[], unsigned len)
{
        int pivot;
        unsigned right, left = 0, stack[64], pos = 0, seed = rand();
        for ( ; ; ) {                                                          /* outer loop */
                for (; left+1 < len; len++) {                          /* sort left to len-1 */
                        if (pos == 64) len = stack[pos = 0];       /* stack overflow, reset */
                        pivot = array[left+seed%(len-left)];       /* pick random pivot */
                        seed = seed*69069+1;                     /* next pseudorandom number */
                        stack[pos++] = len;                         /* sort right part later */
                        for (right = left-1; ; ) {      /* inner loop: partitioning */
                                while (array[++right] < pivot);  /* look for greater element */
                                while (pivot < array[--len]);    /* look for smaller element */
                                if (right >= len) break;           /* partition point found? */
                                array[right] = array[right] ^ array[len];             /* the only swap */
                                array[len]   = array[right] ^ array[len];             /* the only swap */
                                array[right] = array[right] ^ array[len];             /* the only swap */
                        }                            /* partitioned, continue left part */
                }
                if (pos == 0) break;                               /* stack empty? */
                left = len;                             /* left to right is sorted */
                len = stack[--pos];                      /* get next range to sort */
        }
}

int generate_random(size_t len)
{

	srandom(time(NULL));
	return random()%len;
}

int main(int argc, char** argv)
{
	int arry[] = {11,12,13,14,10,2,9,4,7,5,3,6,1,8,0};
	size_t len = sizeof(arry)/sizeof(arry[0]);

	output(arry, len);
	insert_sort(arry, len);
	output(arry, len);
	optimized_select_sort(arry, len);
	output(arry, len);
	optimized_bubble_sort(arry, len);
	output(arry, len);
	bubble_sort(arry, len);

	puts("before quick_sort -------------------------------");
	output(arry, len);
	quick_sort_2(arry, 0, len-1);
	output(arry, len);

	return 0;
}

