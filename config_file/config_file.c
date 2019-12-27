/*************************************************************************
	> File Name: config_file.c
	> Author: linuxidc
	> Mail: linuxidc@linuxidc.com 
	> Created Time: 2019年05月12日 星期日 12时00分15秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#define MAX_LINE_LENGTH    256


#ifdef __cplusplus
#else
	#define bool int
	#define false 0
	#define true (!false)
#endif

#ifndef WIN32  
	#define _atoi64(val)    strtol(val,NULL,10) 
#endif

int read_line(FILE *fp, char *bp)
{
    char c = '\0';
    int i = 0;
    bool isAssgin = 0;
    /* Read one line from the source file */
    while (1)
    {
        c = getc(fp);
        if (c == '\n')
        {
            break;
        }

        if (c == '\r')
        {
            continue;
        }

        if (c == '=')
        {
            isAssgin = 1;
        }

        if (feof(fp))
        {
            /* return FALSE on unexpected EOF */
            if (isAssgin == 1)
            {
                bp[i] = '\0';
                return(1);
            }
            else
            {
                return(0);
            }
        }
        bp[i++] = c;
    }
    bp[i] = '\0';
    return(1);
}
/************************************************************************
* Function:     Get_private_profile_int()
* Arguments:    <char *> section - the name of the section to search for
*               <char *> entry - the name of the entry to find the value of
*               <int> def - the default value in the event of a failed read
*               <char *> file_name - the name of the .ini file to read from
* Returns:      the value located at entry
*************************************************************************/
int Get_private_profile_int(const char *section, const char *entry, int def, char *file_name)
{
    FILE *fp = fopen(file_name, "r");
    //Try to fix the issue that the MAX_PATH should be 256, not 80
    char buff[MAX_LINE_LENGTH];
    char *ep;
    char t_section[MAX_LINE_LENGTH];
    char value[12];
    int len = strlen(entry);
    int i;
    //To support negative number convert
    bool b_IsNegative = false;
    if (!fp)
    {
        return(0);
    }
    sprintf(t_section, "[%s]", section); /* Format the section name */
    /*  Move through file 1 line at a time until a section is matched or EOF */
    do
    {
        if (!read_line(fp, buff))
        {
            fclose(fp);
            return(def);
        }
    }while (strcmp(buff, t_section));
    /* Now that the section has been found, find the entry.
     * Stop searching upon leaving the section's area. */
    do
    {
        if (!read_line(fp, buff) || buff[0] == '[') //130516 Willy modify '\0' to '[' for parser ini bug.
        {
            fclose(fp);
            return(def);
        }
    }while (strncmp(buff, entry, len));
    
    ep = strrchr(buff, '=');   /* Parse out the equal sign */
    ep++;
    if (!strlen(ep))           /* No setting? */
    {
        return(def);
    }
    /* Copy only numbers fail on characters */
    //To support negative number convert
    if (ep[0] == '-')
    {
        b_IsNegative = true;
        for (i = 1; isdigit(ep[i]); i++)
        {
            value[i - 1] = ep[i];
        }
        value[--i] = '\0';
    }
    else
    {
        for (i = 0; isdigit(ep[i]); i++)
        {
            value[i] = ep[i];
        }
        value[i] = '\0';
    }
    fclose(fp);                /* Clean up and return the value */
    //To support negative number convert
    if (b_IsNegative)
    {
        return (0 - atoi(value));
    }
    else  
    {
        return(atoi(value));
    }
}


unsigned long long Get_private_profile_longlong(const char *section, const char *entry, unsigned long long def, char *file_name)
{
    FILE *fp = fopen(file_name, "r");
    char buff[MAX_LINE_LENGTH];
    char *ep;
    char t_section[MAX_LINE_LENGTH];
    char value[16];
    int len = strlen(entry);
    int i;
    if (!fp)
    {
        return(0);
    }
    sprintf(t_section, "[%s]", section); /* Format the section name */
    /*  Move through file 1 line at a time until a section is matched or EOF */
    do
    {
        if (!read_line(fp, buff))
        {
            fclose(fp);
            return(def);
        }
    }while (strcmp(buff, t_section));
    /* Now that the section has been found, find the entry.
     * Stop searching upon leaving the section's area. */
    do
    {
        if (!read_line(fp, buff) || buff[0] == '[') //130516 Willy modify '\0' to '[' for parser ini bug.
        {
            fclose(fp);
            return(def);
        }
    }while (strncmp(buff, entry, len));
    
    ep = strrchr(buff, '=');   /* Parse out the equal sign */
    ep++;
    if (!strlen(ep))           /* No setting? */
    {
        return(def);
    }
    /* Copy only numbers fail on characters */
    for (i = 0; isdigit(ep[i]); i++)
    {
        value[i] = ep[i];
    }
    value[i] = '\0';
    fclose(fp);                /* Clean up and return the value */
    return(_atoi64(value));
}

/**************************************************************************
* Function:     Get_private_profile_string()
* Arguments:    <char *> section - the name of the section to search for
*               <char *> entry - the name of the entry to find the value of
*               <char *> def - default string in the event of a failed read
*               <char *> buffer - a pointer to the buffer to copy into
*               <int> buffer_len - the max number of characters to copy
*               <char *> file_name - the name of the .ini file to read from
* Returns:      the number of characters copied into the supplied buffer
***************************************************************************/
int Get_private_profile_string(const char *section, const char *entry, const char *def, char *buffer, int buffer_len, char *file_name)
{

    FILE *fp = fopen(file_name, "r");
    char buff[MAX_LINE_LENGTH];
    char *ep;
    char t_section[MAX_LINE_LENGTH];
    int len = strlen(entry);
    if (!fp)
    {
        return(0);
    }
    sprintf(t_section, "[%s]", section);  /* Format the section name */
    /*  Move through file 1 line at a time until a section is matched or EOF */
    do
    {
        if (!read_line(fp, buff))
        {
            strncpy(buffer, def, buffer_len);
            return(strlen(buffer));
        }
    }while (strcmp(buff, t_section));
    /* Now that the section has been found, find the entry.
     * Stop searching upon leaving the section's area. */
    do
    {
        if (!read_line(fp, buff) || buff[0] == '[') //130516 Willy modify '\0' to '[' for parser ini bug.
        {
            fclose(fp);
            strncpy(buffer, def, buffer_len);
            return(strlen(buffer));
        }
    }while (strncmp(buff, entry, len));

    ep = strrchr(buff, '=');   /* Parse out the equal sign */
    do
    {
        ep++;
    }while(!strncmp(ep, " ", 1));   //Remove the blank space

    /* Copy up to buffer_len chars to buffer */
    strncpy(buffer, ep, buffer_len - 1);
    buffer[buffer_len - 1] = '\0';
    fclose(fp);               /* Clean up and return the amount copied */
    return(strlen(buffer));
}
int Get_private_profile_hex(const char *section, const char *entry, int def, char *file_name)
{
    char valBuf[16], valBuf2[16];
    int data;

    memset(valBuf, 0, sizeof(valBuf));
    memset(valBuf2, 0, sizeof(valBuf2));

    sprintf(valBuf2, "0x%x", def);
    Get_private_profile_string(section, entry, valBuf2, &valBuf[0], sizeof(valBuf), file_name);
    data = 0;
    sscanf(valBuf, "0x%x", &data);
    return data;
}

/*************************************************************************
 * Function:    Write_private_profile_string()
 * Arguments:   <char *> section - the name of the section to search for
 *              <char *> entry - the name of the entry to find the value of
 *              <char *> buffer - pointer to the buffer that holds the string
 *              <char *> file_name - the name of the .ini file to read from
 * Returns:     TRUE if successful, otherwise FALSE
 *************************************************************************/
int Write_private_profile_string(const char *section, const char *entry, char *buffer, char *file_name)
{
    FILE *rfp, *wfp;
    char tmp_name[15];
    //Try to fix the issue that the MAX_PATH should be 256, not 80
    char buff[MAX_LINE_LENGTH];
    char t_section[MAX_LINE_LENGTH];
    int len = strlen(entry);
    tmpnam(tmp_name); /* Get a temporary file name to copy to */
    sprintf(t_section, "[%s]", section); /* Format the section name */

    rfp = fopen(file_name, "r");
    if (!rfp)  /* If the .ini file doesn't exist */
    {
        wfp = fopen(file_name, "w");
        if (!wfp) /*  then make one */
        {
            return(0);
        }
        fprintf(wfp, "%s\n", t_section);
        fprintf(wfp, "%s=%s\n", entry, buffer);
        fclose(wfp);
        return(1);
    }

    wfp = fopen(tmp_name, "w");
    if (!wfp)
    {
        fclose(rfp);
        return(0);
    }

    /* Move through the file one line at a time until a section is
     * matched or until EOF. Copy to temp file as it is read. */
    do
    {
        if (!read_line(rfp, buff))
        {
            /* Failed to find section, so add one to the end */
            fprintf(wfp, "\n%s\n", t_section);
            fprintf(wfp, "%s=%s\n", entry, buffer);
            /* Clean up and rename */
            fclose(rfp);
            fclose(wfp);
            unlink(file_name);
            rename(tmp_name, file_name);
            return(1);
        }
        fprintf(wfp, "%s\n", buff);
    }while (strcmp(buff, t_section));

    /* Now that the section has been found, find the entry. Stop searching
     * upon leaving the section's area. Copy the file as it is read
     * and create an entry if one is not found.  */
    while (1)
    {
        if (!read_line(rfp, buff))
        {
            /* EOF without an entry so make one */
            fprintf(wfp, "%s=%s\n", entry, buffer);
            /* Clean up and rename */
            fclose(rfp);
            fclose(wfp);
            unlink(file_name);
            rename(tmp_name, file_name);
            return(1);

        }
        if (!strncmp(buff, entry, len) || buff[0] == '\0')
        {
            break;
        }
        fprintf(wfp, "%s\n", buff);
    }

    if (buff[0] == '\0')
    {
        fprintf(wfp, "%s=%s\n", entry, buffer);
        do
        {
            fprintf(wfp, "%s\n", buff);
        }
        while (read_line(rfp, buff));
    }
    else
    {
        fprintf(wfp, "%s=%s\n", entry, buffer);
        while (read_line(rfp, buff))
        {
            fprintf(wfp, "%s\n", buff);
        }
    }
    /* Clean up and rename */
    fclose(wfp);
    fclose(rfp);
    unlink(file_name);
    rename(tmp_name, file_name);
    return(1);
}

int Write_private_profile_int(const char *section, const char *entry, int data, char *file_name)
{
    char valBuf[16];
    memset(valBuf, 0, 16);
    sprintf(valBuf, "%d", data);
    return Write_private_profile_string(section, entry, valBuf, file_name);
}

unsigned long long Write_private_profile_longlong(const char *section, const char *entry, unsigned long long data, char *file_name)
{
    char valBuf[16];
    memset(valBuf, 0, 16);
    sprintf(valBuf, "%Lu", data);
    return Write_private_profile_string(section, entry, valBuf, file_name);
}
