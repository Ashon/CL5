/**
 *
 * CL5 - lesson 5
 *
 * @author ashon
 * @date 2014-04-11
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF 255
#define MAX_LINE 100

void prnt_str(char* str)
{
    char* cur;
    
    for(cur = str; *cur != 0; cur++)
        printf("%p -> '%c', %d]\n", cur, *cur, *cur);
}

unsigned long long strtoul_strict(char* str)
{
    char* cur;

    for(cur = str; *cur != 0; cur++)
        if(!(47 < *cur && *cur < 58))
            return 0;

    return strtoul(str, NULL, 10);
}

int cmp_ws(char c)
{
    char ws[] = " \t";
    char* cur_ws;

    for(cur_ws = ws; *cur_ws != 0; cur_ws++) {
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
unsigned long long read_number()
{
    unsigned long long number;
    char* buf = (char*)calloc(MAX_BUF, sizeof(char));

    fgets_safe(buf, MAX_BUF, stdin);
    trim_ws(buf);
    number = strtoul_strict(buf);

    free(buf);

    return number;
}

/**
 * mode validation.
 */
unsigned long long get_mode(unsigned long long number)
{
    switch(number) {
        case 1:
            printf("# draw lower triangle\n");
            return 1;
        case 2:
            printf("# draw upper triangle\n");
            return 2;
        case 3:
            printf("# draw diamond triangle\n");
            return 3;
    }
    return 0;
}

/*
 * draw diamond parts..
 */
void draw_dia_part(unsigned long long lines, unsigned long long i)
{
    unsigned long j;
    for(j = (lines + 1 >> 1) - i; 0 < j; j--)
        printf(" ");
    for(j = 0; j < (i << 1) - 1; j++)
        printf("*");
    printf("\n");
}

/**
 * draw shapes.
 */
int draw(unsigned long long mode)
{
    unsigned long long lines;
    unsigned long long i, j;
    
    if(mode == 0)
        return 1;

    printf("input lines..(1 to 100%s > ", mode == 3 ? ", odd numbers only..)" : ")");
    lines = read_number();
    
    if(0 < lines && lines < MAX_LINE + 1) {
        switch(mode){
            case 1:
                for(i = 1; i < lines + 1; i++) {
                    for(j = 0; j < i; j++)
                        printf("*");
                   printf("\n");
                }
            break;
            case 2:
                for(i = lines; 0 < i; i--) {
                    for(j = 0; j < i; j++)
                        printf("*");
                    printf("\n");
                }
            break;
            case 3:
                if((lines & 0x1) != 1)
                    return 1;
                for(i = 1; i < (lines + 1) >> 1; i++)
                    draw_dia_part(lines, i);
                for(i = (lines + 1) >> 1; 0 < i; i--)
                    draw_dia_part(lines, i);
            break;
        } // end switch
        return 0;
    } // end if
    return 1;
}

/*
 * print menu
 */
void print_menu()
{
    printf("# Draw Pattern.\n");
    printf(" 1 - lower triangle\n");
    printf(" 2 - upper triangle\n");
    printf(" 3 - diamond\nselect mode > ");
}

// main
int main()
{
    unsigned long long mode;
    while(1) {
        print_menu();
        if(!(mode = get_mode(read_number()))) {
            printf("invalid mode..\n");
            continue;
        }
        if(!(draw(mode))){
            printf("bye.\n");
            return 0;
        }
        printf("invalid line number..\n");
    }
}
