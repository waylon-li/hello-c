#include <stdio.h>


int main(int argc, char *argv[])
{
	char *str = "abcdefg";
	printf("%s\v", str);
	printf("\b\b%s\v", str);
	printf("%s\n", str);
	
	return 0;
}
