#include <stdio.h>
#include <assert.h>

int my_atoi(char *str)
{
	int retval = 0;
	char *ptr = str;
	char *pstr = str;
	if(NULL == str) return 0;
	
	while(*ptr == ' ' || *ptr == '\t') {
		ptr++;
		pstr = ptr;
	}
	
	while(*ptr) {
		if(*ptr >= '0' && (*ptr) <= '9') {
			retval = retval*10 + (*ptr)-'0';
		}
		else if((*ptr == '-' && ptr == pstr) || (*ptr=='+' && ptr==pstr)) {
			;
		}
		else {
			break;
		}
		ptr++;
	}

	return pstr[0]=='-'?-retval:retval;
}

void test()
{
	assert(0 == my_atoi("-00000"));
	assert(-89 == my_atoi("-89"));
	assert(890 == my_atoi("0890"));
	assert(890 == my_atoi("+0890"));
	assert(890 == my_atoi("    0890"));
	assert(890 == my_atoi("    +0890"));
	assert(-890 == my_atoi("    -0890"));
	//assert(2147483648 == my_atoi("2147483648"));
}


int main(int argc, char** argv)
{
	char array[] = "2147483648";
	test();

	printf("%s\n", array);
	printf("%d\n", my_atoi(array));
	printf("%u\n", my_atoi(array));

	return 0;
}

