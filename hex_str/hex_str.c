#include <stdio.h>

int main()
{
   /* 我的第一个 C 程序 */
   printf("Hello, World! \n");
	
	char *str_a = "\x31";
	char *str_b = "\x3132";
	char *str_c = "\x31323334";
	
	char arr_a[] = "\x31";
	char arr_b[] = "\x3132";
	char arr_c[] = "\x313233 34";
	
	printf("str_a: %s, sizeof(str_a): %d\n", str_a, sizeof(str_a));
	printf("str_b: %s, sizeof(str_b): %d\n", str_b, sizeof(str_b));
	printf("str_c: %s, sizeof(str_c): %d\n", str_c, sizeof(str_c));
	
	printf("arr_a: %s, sizeof(arr_a): %d\n", arr_a, sizeof(arr_a));
	printf("arr_b: %s, sizeof(arr_b): %d\n", arr_b, sizeof(arr_b));
	printf("arr_c: %s, sizeof(arr_c): %d\n", arr_c, sizeof(arr_c));
   
   return 0;
}

/* output */
/*
Hello, World! 
str_a: 1, sizeof(str_a): 8
str_b: 2, sizeof(str_b): 8
str_c: 4, sizeof(str_c): 8
arr_a: 1, sizeof(arr_a): 2
arr_b: 2, sizeof(arr_b): 2
arr_c: 3 34, sizeof(arr_c): 5
*/
