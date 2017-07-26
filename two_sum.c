#include <stdio.h>
#include <stdlib.h>

/*
   * Note: The returned array must be malloced, assume caller calls free().
    */
int* two_sum(int* nums, int len, int target)
{
	int i,j;
	int *array = malloc(sizeof(int) * 2);

	for(i=0; i<len; i++) {
		array[0] = i;
		for(j=0; j<len; j++) {
			if(i == j || nums[i] == nums[j]) {
				continue;
			}
			if(nums[i] + nums[j] == target) {
				array[1] = j;
				return array;
			}
		}
	}

	array[0] = -1;
	array[1] = -1;
	return array;
}


int main(int argc, char** argv)
{
	int array[] = {2, 7, 11, 15};
	size_t len = sizeof(array)/sizeof(array[0]);
	int target = 9;
	int *retval = two_sum(array, len, target);

	printf("%d, %d\n", retval[0], retval[1]);


	return 0;
}
