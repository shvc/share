#include <stdio.h>

size_t strlen(const char* str)
{
	size_t len = 0;
	for(len=0; *str; len++, str++);
	return len;
}

char* strncpy(char* dst, const char* src, size_t cnt)
{
	char *p = NULL;

	if(dst == src) {
		return dst;
	} else if(dst < src) {
		p = dst;
		while(cnt) {
			*p++ = *src++;
			cnt--;
		}
	} else {
		p = dst + cnt;
		src = src + cnt;
		while(cnt) {
			*--p = *--src;
			cnt--;
		}
		
	}
	return dst;
}

char * strreplace(char* str, char* sub, char* rep)
{
	size_t sub_len, rep_len;
	char *p, *p1, *q;

	sub_len = strlen(sub);
	rep_len = strlen(rep);
	for(p=str; *p != 0; p++) {
		for(p1=p, q=sub; *p1==*q && *q; p1++, q++);
		if(*q) continue;
		
		if(sub_len != rep_len) {
			strncpy(p+rep_len, p+sub_len, strlen(p+sub_len) + 1);
		}
		strncpy(p, rep, rep_len);
		p += rep_len;
	}

	return str;
}


int main(int argc, char** argv)
{
	int ret;
	char a[100] = "abcdefg, abcdefg, abcdefg";
	char b[] = "bcd";
	char c[] = "12345678";
	char d[] = "xzy";

	printf("before: %s\n", a);
	printf("sub   : %s\n", b);
	printf("rep   : %s\n", c);
	strreplace(a, b, c);
	printf("after : %s\n", a);

	puts("========================");
	printf("before: %s\n", a);
	printf("sub   : %s\n", c);
	printf("rep   : %s\n", d);
	strreplace(a, c, d);
	printf("after : %s\n", a);


	return ret;
}
