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
	char *pstr, *p, *psub;

	sub_len = strlen(sub);
	rep_len = strlen(rep);

	for(pstr=str; *pstr != 0; pstr++) {
		for(p=pstr, psub=sub; *p==*psub && *psub; p++, psub++);
		if(*psub) continue;
		
		if(sub_len != rep_len) {
			strncpy(pstr+rep_len, pstr+sub_len, strlen(pstr+sub_len) + 1);
		}
		strncpy(pstr, rep, rep_len);
		pstr += rep_len;
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

	puts("=================================");
	printf("before: %s\n", a);
	printf("sub   : %s\n", c);
	printf("rep   : %s\n", d);
	strreplace(a, c, d);
	printf("after : %s\n", a);

	puts("=================================");
	printf("before: %s\n", a);
	printf("sub   : %s\n", d);
	printf("rep   : %s\n", b);
	strreplace(a, d, b);
	printf("after : %s\n", a);

	return ret;
}
