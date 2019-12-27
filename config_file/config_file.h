/*************************************************************************
	> File Name: config_file.h
	> Author: linuxidc
	> Mail: linuxidc@linuxidc.com 
	> Created Time: 2019年05月12日 星期日 12时03分11秒
 ************************************************************************/

#ifndef _CONFIGFILE_H_
#define _CONFIGFILE_H_

extern int Get_private_profile_int(const char *section, const char *entry, int def, char *file_name);
extern unsigned long long Get_private_profile_longlong(const char *section, const char *entry, unsigned long long def, char *file_name);
extern int Get_private_profile_string(const char *section, const char *entry, const char *def, char *buffer, int buffer_len, char *file_name);
extern int Get_private_profile_hex(const char *section, const char *entry, int def, char *file_name);

extern int Write_private_profile_string(const char *section, const char *entry, char *buffer, char *file_name);
extern int Write_private_profile_int(const char *section, const char *entry, int data, char *file_name);
extern unsigned long long Write_private_profile_longlong(const char *section, const char *entry, unsigned long long data, char *file_name);

#endif //_CONFIGFILE_H_
