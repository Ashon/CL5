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
#define MAX_LINE 100

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

/*
 * read lines.
 */
ULL read_lines(ULL mode)
{
    ULL lines;
    printf("input lines..(1 to %d%s > ",
        MAX_LINE, mode == 3 ? ", odd numbers only..)" : ")");
    lines = read_number();

    if(mode == 3)
        if((lines & 0x1) != 1)
            return 0;

    if(0 < lines && lines < MAX_LINE + 1)
        return lines;
}

/**
 * read mode.
 */
ULL read_mode()
{
    printf("\n# Draw Pattern.\n");
    printf(" 1 - lower triangle\n");
    printf(" 2 - upper triangle\n");
    printf(" 3 - diamond\n");
    printf(" 4 - parallelogram\n");
    printf(" 5 - upper obtuse triangle\n");
    printf("select mode > ");

    switch(read_number()) {
        case 1:
            printf("\n# draw lower triangle\n");
            return 1;
        case 2:
            printf("\n# draw upper triangle\n");
            return 2;
        case 3:
            printf("\n# draw diamond triangle\n");
            return 3;
        case 4:
            printf("\n# draw parallelogram\n");
            return 4;
        case 5:
            printf("\n# draw upper obtuse triangle\n");
            return 5;
    }
    printf("# invalid mode number..\n");
    return 0;
}


