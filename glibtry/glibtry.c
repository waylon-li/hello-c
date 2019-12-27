/*
 * glibtry.c
 *
 *  Created on: 2018年5月22日
 *      Author: waylon
 */
#include <stdio.h>
#include <glib.h>
int main(int argc, char** argv)
{
    GList* list=NULL;
    list=g_list_append(list,"Hello world!");
    list=g_list_append(list,"made by pcat");
    list=g_list_append(list,"http://pcat.cnblogs.com");
    printf("The first item is %s\n",g_list_first(list)->data);
    return 0;
}
