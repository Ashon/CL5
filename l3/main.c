/**
 *
 * CL5 - lesson 3
 *
 * @author ashon
 * @date 2014-04-07
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF 255

// for debugging..
void prnt_str(char* str)
{
    char* cur;
    
    for(cur = str; *cur != 0; cur++)
        printf("%p -> '%c', %d]\n", cur, *cur, *cur);
}

/**
 * validates input value.
 * input value must be numeric.
 * it returns 0 when occurs an error.
 *
 * @param
 *    str - input value.
 *
 * @return
 *    0 - error
 */
unsigned long long strtoul_strict(char* str)
{
    char* cur;

    for(cur = str; *cur != 0; cur++)
        if(!('0' < *cur && *cur < '9'))
            return 0;

    return strtoul(str, NULL, 10);
}

/**
 * compare whitespace.
 *
 * whitespace -> ' ', '\t'
 * 
 * @param
 *    char - character
 *
 * @return 
 *    0 - equal
 *    1 - not equal
 */
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

/**
 * trims whitespaces in first & end of the string.
 * 
 * scratch..
 *
 * 0. if string == 0 then
 *      return 0
 *
 *    else..
 *
 * 1. initialize *cur, anc_start, anc_end.
 *
 * string[] = "   123  "
 *             ^        *str, *cur
 *             ^        *anc_start
 *                    ^ *anc_end
 *
 * 2. set each anchor points to start & end of character.
 * 
 * string[] = "   123  "
 *             ^        *str, *cur
 *             ---^     *anc_start
 *                   ^- *anc_end
 *
 * 3. start iteration - copy *anchor++ to *cursor++.
 *
 * iteration #0 >
 * string[] = "1  123  "
 *             ^        *str, *cur
 *             ---^     *anc_start
 *                   ^- *anc_end
 *
 * iteration #1 >
 * string[] = "12 123  "
 *             ^        *str
 *             -^       *cur
 *             ----^    *anc_start
 *                   ^- *anc_end
 *
 * ... repeat.
 * (termination condition -> *anc_start >= *anc_end)
 *
 * 4. set '\0' to end of trimmed string.
 *
 * string[] = "123\23  "
 *                ^     '\0' - end of string.
 *
 * 5. return sting[].
 *
 * @param
 *    str - input value.
 *
 * @return
 *    string - trimmed string.
 *    0 - str equals 0.
 *
 * @deprecated
 */
char* trim_ws(char* str)
{
    char* cur;
    char* anc_start;
    char* anc_end;

    // 1
    cur = str;
    anc_start = str;
    anc_end = str + strlen(str) - 1;

    // 2
    for(; anc_start < anc_end && !cmp_ws(*anc_start); anc_start++);
    for(; cur < anc_end && !cmp_ws(*anc_end); anc_end--);

    // 3
    for(; anc_start < anc_end + 1; *cur++ = *anc_start++);

    // 4
    *cur = 0;

    // 5
    return str;
}

/**
 * prevents some trim_ws()'s problems.
 *
 * @param
 *    str - string
 *
 * @return
 *    char* - trimmed string
 */
char* trim_ws_safe(char* str)
{

}

/**
 * prevents some fgets()'s problems.
 * 
 * @param
 *    str - string pointer
 *    size - size of buffer
 *    stream - input stream
 *
 * @return
 *    char* - pointer of str.
 */
char* fgets_safe(char *str, int size, FILE* stream)
{
    int length;

    fgets(str, size, stream);
    length = strlen(str);

    /*
     * before :
     * str[length - 1] =0;
     *
     * after :
     */
    if(0 < length && str[length - 1] == '\n')
        str[length - 1] = 0;

    return str;
}

void dbg_trim_ws(){
    printf("trim_ws(\"\") ..");
    trim_ws("");
    printf("clear\n");

    printf("trim_ws(\\0) ..");
    trim_ws(0);
    printf("clear\n");

    printf("trim_ws(-1)");
    trim_ws("asdfasdf");
    printf("clear\n");

}

// main
int main()
{
    char* buf = (char*)calloc(MAX_BUF, sizeof(char));
    unsigned long long num;
    int i, j;

    dbg_trim_ws();

    while(1) {
        printf("How many lines? (1..100) ");

        fgets_safe(buf, MAX_BUF, stdin);
        trim_ws(buf);

        num = strtoul_strict(buf);

        if(0 < num && num < 101) {
            num++;
            for(i = 1; i < num; i++) {
                for(j = 0; j < i; j++)
                    printf("*");
                printf("\n");
            }
            free(buf);
            return 0;
        } else
            printf("Invalid input - Range 1..100\n");
    }
}
