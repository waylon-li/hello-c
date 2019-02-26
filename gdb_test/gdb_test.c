/*************************************************************************
	> File Name: ./gdb_test.c
	> Author: waylon
	> Mail: waylon_li@ghotmail.com 
	> Created Time: 2019年02月26日 星期二 10时44分27秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if(argc != 2){
		printf("run %s 0xbffff3a4\n", argv[0]);
		return -1;
	}
	int n = strtol(argv[1], NULL, 16);
	printf("%d,%x\n", n, n);
	return 0;
}
