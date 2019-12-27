/*************************************************************************
	> File Name: main.c
	> Author: linuxidc
	> Mail: linuxidc@linuxidc.com 
	> Created Time: 2019年05月12日 星期日 13时01分20秒
 ************************************************************************/

#include<stdio.h>
#include "ini_file.h"

#define INIFILE_TEST_THIS_FILE
#ifdef INIFILE_TEST_THIS_FILE
#define INIFILE_TEST_READ_AND_WRITE
int main (void)
{
	printf ("Hello World\n");
	OpenIniFile ("Test.ini");
#ifdef INIFILE_TEST_READ_AND_WRITE
	WriteString  ("Test", "Name", "Value");
	WriteString  ("Test", "Name", "OverWrittenValue");
	WriteString  ("Test", "Port", "COM1");
	WriteString  ("Test", "User", "James Brown jr.");
	WriteString  ("Configuration", "eDriver", "MBM2.VXD");
	WriteString  ("Configuration", "Wrap", "LPT.VXD");
	WriteInt 	 ("IO-Port", "Com", 2);
	WriteBool 	 ("IO-Port", "IsValid", 0);
	WriteDouble  ("TheMoney", "TheMoney", 67892.00241);
	WriteInt     ("Test"    , "ToDelete", 1234);
	WriteIniFile ("Test.ini");
	
	//OpenIniFile  ("Test.ini");
	DeleteKey    ("Test"	  , "ToDelete");
	WriteIniFile ("Test.ini");
#endif
	printf ("[Test] Name = %s\n", ReadString ("Test", "Name", "NotFound"));
	printf ("[Test] Port = %s\n", ReadString ("Test", "Port", "NotFound"));
	printf ("[Test] User = %s\n", ReadString ("Test", "User", "NotFound"));
	printf ("[Configuration] eDriver = %s\n", ReadString ("Configuration", "eDriver", "NotFound"));
	printf ("[Configuration] Wrap = %s\n", ReadString ("Configuration", "Wrap", "NotFound"));
	printf ("[IO-Port] Com = %d\n", ReadInt ("IO-Port", "Com", 0));
	printf ("[IO-Port] IsValid = %d\n", ReadBool ("IO-Port", "IsValid", 0));
	printf ("[TheMoney] TheMoney = %1.10lf\n", ReadDouble ("TheMoney", "TheMoney", 111));
	CloseIniFile ();
	return 0;
}
#endif
