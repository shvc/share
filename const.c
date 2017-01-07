int main()
{
	const int ret = 0;
	int *p = (int*)&ret;

	*p = 4;

	return *p;
}

