/* 从键盘缓冲区读取字符，getchar() 仅当遇到回车时才开始执行 */

#include <stdio.h>


int main()
{
	char c;
	for(;(c = getchar()) != '\n';)
	putchar(c);

	putchar('\n');

	return 0;	
}
