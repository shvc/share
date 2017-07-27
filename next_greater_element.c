#include <stdio.h>
#include <stdlib.h>
/*
 * https://leetcode.com/problems/next-greater-element-i/
 */

int* next_greater_element(int* find_nums, int find_len, int* nums, int nums_len, int* ret_size)
{
	int* array;
	int i,j,k;

	array = malloc(sizeof(int) * find_len);
	*ret_size = find_len;

	for(i=0; i<find_len; i++) {
		array[i] = -1;
		for(j=0; j<nums_len; j++) {
			if(find_nums[i] == nums[j]) {
				for(k=j; k<nums_len; k++) {
					if(nums[k] > find_nums[i]) {
						array[i] = nums[k];
						break;
					}
				}
				break;
			}
		}
	}

	return array;

}


int main(void)
{
	int nums1[] = {4,1,2};
	int nums2[] = {1,3,4,2};
	int i, ret, *ptr;

	size_t len1 = sizeof(nums1)/sizeof(nums1[0]);
	size_t len2 = sizeof(nums2)/sizeof(nums2[0]);

	ptr = next_greater_element(nums1, len1, nums2, len2, &ret);

	for(i=0; i<ret; i++) {
		printf("%2d, ", ptr[i]);
	}

	puts("");

	return 0;
} 

