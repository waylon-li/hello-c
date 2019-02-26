/*************************************************************************
	> File Name: ./gdb_test.c
	> Author: waylon
	> Mail: waylon_li@ghotmail.com 
	> Created Time: 2019年02月26日 星期二 10时44分27秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void getmem(void **p, int num)
{
	*p = (void *)malloc(num);
}

void func(void)
{
	char *str = NULL;
	getmem((void **)&str, 20);
	strcpy(str, "Hello gdb");
	printf("%s\n", str);
	free(str);

}

int main(int argc, char **argv)
{
	if(argc != 2){
		printf("run %s 0xbffff3a4\n", argv[0]);
		return -1;
	}
	int n = strtol(argv[1], NULL, 16);
	printf("%d,%x\n", n, n);

	int quit_sig = 0;
	while(1){
		if(quit_sig == 1){
			func();
			return 1;
		}
		sleep(3);
	}
	return 0;
}
