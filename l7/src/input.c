/**
 * CL5 - lesson 7
 *
 * input.c
 *
 * @author ashon
 * @date 2014-04-15
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF 255

// var type ULL - unsigned long long
#define ULL unsigned long long

ULL strtoul_strict(char* str)
{
    char* cur;

    for(cur = str; *cur; cur++)
        if(!(47 < *cur && *cur < 58))
            return 0;

    return strtoul(str, NULL, 10);
}

int cmp_ws(char c)
{
    char ws[] = " \t";
    char* cur_ws;

    for(cur_ws = ws; *cur_ws; cur_ws++) {
        if(c != *cur_ws)
            continue;
        return 0;
    }

    return 1;
}

char* trim_ws(char* str)
{
    char* cur = str;
    char* anc_start = str;
    char* anc_end = str + strlen(str) - 1;

    for(; anc_start < anc_end && !cmp_ws(*anc_start); anc_start++);
    for(; cur < anc_end && !cmp_ws(*anc_end); anc_end--);

    for(; anc_start < anc_end + 1; *cur++ = *anc_start++);

    *cur = 0;

    return str;
}

char* fgets_safe(char *str, int size, FILE* stream)
{
    int length;

    fgets(str, size, stream);
    length = strlen(str);

    if(0 < length && str[length - 1] == '\n')
        str[length - 1] = 0;

    return str;
}

/**
 * read number 
 */
ULL read_number()
{
    ULL number;
    char* buf = (char*)calloc(MAX_BUF, sizeof(char));

    fgets_safe(buf, MAX_BUF, stdin);
    trim_ws(buf);
    number = strtoul_strict(buf);

    free(buf);

    return number;
}

