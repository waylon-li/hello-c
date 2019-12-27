/*************************************************************************
	> File Name: array_and_ptr.c
	> Author: waylon
	> Mail: waylon_li@ghotmail.com 
	> Created Time: 2018年12月03日 星期一 23时23分26秒
 ************************************************************************/
#include <stdio.h>
#include <malloc.h>


char ga[10] = "abcdefg";

void print_arg(char ca[])
{
	printf("&ca %d, &(ca[0]) %d, &(ca[1]) %d\n", &ca, &(ca[0]), &(ca[1]) );
}

void print_ptr(char *pa)
{
	printf("&pa %d, &(pa[0]) %d, &(pa[1]) %d \n", &pa, &(pa[0]), &(pa[1]) );
	printf("++pa %d \n", ++pa );
}

int main(int argc, char **argv)
{
	char arr[10];
	print_arg(arr);
	
	char *ptr = (char *)malloc(10);
	print_ptr(ptr);

	print_arg(ga);
	print_ptr(ga);

	printf("&ga %d, &(ga[0]) %d, &(ga[1]) %d\n", &ga, &(ga[0]), &(ga[1]) );

	return 0;
}

