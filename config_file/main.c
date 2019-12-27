/*************************************************************************
	> File Name: main.c
	> Author: linuxidc
	> Mail: linuxidc@linuxidc.com 
	> Created Time: 2019年05月12日 星期日 12时04分22秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "config_file.h"
#define DEFAULT_INI_FILE "/Autoconfig.ini"

int main(int argc, char* argv[])
{
    char ProductModel[80];
    char iniFile[256];
    char *buffer;
    buffer = getcwd(NULL, 0);
    strcpy(iniFile, buffer);
    strcat(iniFile,DEFAULT_INI_FILE);

    Get_private_profile_string("Setting", "ProductModel", "SS", ProductModel, sizeof(ProductModel), iniFile);
    printf("ProductModel:%s\n",ProductModel);

    unsigned char enExtendBlock = Get_private_profile_int("FwSetting", "EnExtendBlock", 1, iniFile);
    printf("enExtendBlock:%d\n",enExtendBlock);

    int MPVersion = 100;
    Write_private_profile_int("Setting", "MPVersion", MPVersion, iniFile);

    sprintf(ProductModel,"ABCSFE!!221");
    Write_private_profile_string("Setting", "ProductModel", ProductModel, iniFile);

}
