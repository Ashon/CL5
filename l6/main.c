/**
 *
 * CL5 - lesson 6
 *
 * @author ashon
 * @date 2014-04-13
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF 255
#define MAX_LINE 100

// var type ULL - unsigned long long
#define ULL unsigned long long

/**
 * single list of draw_cmd.
 */
typedef struct cmd_node_ {
    void(*cmd)(ULL, ULL, ULL);
    struct cmd_node_* next;
} cmd_node;

/**
 * add
 */
cmd_node* add_cmd_node(cmd_node* n, void(*cmd)(ULL, ULL, ULL))
{
    cmd_node* target = (cmd_node*)malloc(sizeof(cmd_node));
    target->cmd = cmd;

    if(n)
        n->next = target;
    target->next = 0;
    return target;
}

/**
 * getter
 */
void* get_cmd(cmd_node* n)
{
    return n->cmd;
}

/*
 * free node
 *
 * init. p = head
 *    head -> [ ]-> [ ]-> [ ]-> ... -> 0
 *             ^ - *p
 * case 0: sizeof head == 0
 *    return 0;
 *
 * case 1: size of head == 1
 *  i. head -> [ ]
 *             ^ - *p
 *  1. free(p)
 *    head -> [x]
 *             ^ - *p
 *  
 * case 2: size of head > 1
 *  i. head -> [ ]-> [ ]-> [ ]-> ... -> 0
 *             ^ - *p
 * ## do loop
 *  1. q = p
 *    head -> [ ]-> [ ]-> [ ]-> ... -> 0
 *             ^ - *p, *q
 *
 *  2. p = p->next
 *    head -> [ ]-> [ ]-> [ ]-> ... -> 0
 *             =     ^ - *p
 *             ^ - *q
 *  3. free(q)
 *    head -> [x]-> [ ]-> [ ]-> ... -> 0
 *             =     ^ - *p
 *             ^ - *q
 *
 * ## while ( p != null )
 *    head -> [x]-> [x]-> [x]-> ... [x]-> 0
 *             =     =     =    =..  =    ^ - *p
 *             =     =     =    =..  ^ - *q
 *  
 * @param
 *    cmd_node* - head of draw command list
 *
 * @return
 *    0 - 
 */
int free_node(cmd_node* head)
{
    cmd_node* p = head;
    cmd_node* q;
    do {
        q = p;
        p = p->next;
        free(q);
    } while(p);
    return 0;
}

void prnt_str(char* str)
{
    char* cur;
    
    for(cur = str; *cur; cur++)
        printf("%p -> '%c', %d]\n", cur, *cur, *cur);
}

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

    return 0;
}

/*
 * draw strategies..
 */
void draw_loop_up(ULL lines, cmd_node* head)
{
    ULL i, j;
    cmd_node* cur;
    for(i = 1; i < lines + 1; i++) {
        for(cur = head; cur; cur = cur->next)
            if(cur->cmd)
                cur->cmd(lines, i, j);
        printf("\n");
    }
}

void draw_loop_down(ULL lines, cmd_node* head)
{
    ULL i, j;
    cmd_node* cur;
    for(i = lines - 1; 0 < i; i--) {
        for(cur = head; cur; cur = cur->next)
            if(cur->cmd)
                cur->cmd(lines, i, j);
        printf("\n");
    }
}
/*
 * draw pattern Commands
 *
 * command function type
 *  void(*)(ULL, ULL, ULL)
 */
void draw_dia_gap(ULL lines, ULL i, ULL j)
{
    for(j = lines - i; 0 < j; j--)
        printf(" ");
}

void draw_dia_part(ULL lines, ULL i, ULL j)
{
    for(j = 0; j < (i << 1) - 1; j++)
        printf("*");
}

void draw_lower_part(ULL lines, ULL i, ULL j)
{
    for(j = 0; j < i; j++)
        printf("*");
}

void draw_upper_gap(ULL lines, ULL i, ULL j)
{
    for(j = lines - i; 0 < j; j--)
        printf(" ");
}

void draw_upper_part(ULL lines, ULL i, ULL j)
{
    for(j = lines + 1 - i; 0 < j; j--)
        printf("*");
}

void draw_parallelo_part(ULL lines, ULL i, ULL j)
{
    for(i = 0; i < lines; i++)
        printf("*");
}

/**
 * draw shapes.
 */
int draw(ULL mode)
{
    ULL lines;
    ULL i, j;

    cmd_node* head;
    cmd_node* cur;

    void(*loop)(ULL, cmd_node*) = 0;

    if(mode == 0)
        return 1;

    lines = read_lines(mode);

    if(lines) {
        head = add_cmd_node(0, 0);
        cur = head;
        switch(mode){
            case 1:
                cur = add_cmd_node(cur, draw_lower_part);
                loop = draw_loop_up;
            break;
            case 2:
                cur = add_cmd_node(cur, draw_upper_part);
                loop = draw_loop_up;
            break;
            case 3:
                lines = (lines + 1) >> 1;
                cur = add_cmd_node(cur, draw_dia_gap);
                cur = add_cmd_node(cur, draw_dia_part);
                draw_loop_up(lines, head);
                free_node(head);

                head = add_cmd_node(0, 0);
                cur = head;
                cur = add_cmd_node(cur, draw_dia_gap);
                cur = add_cmd_node(cur, draw_dia_part);
                loop = draw_loop_down;
           break;
            case 4:
                cur = add_cmd_node(cur, draw_upper_gap);
                cur = add_cmd_node(cur, draw_parallelo_part);
                loop = draw_loop_up;
            break;
            case 5:
                cur = add_cmd_node(cur, draw_upper_gap);
                cur = add_cmd_node(cur, draw_upper_part);
                loop = draw_loop_up;
            break;
        } // end switch

        // draw
        if(loop)
            loop(lines, head);

        // free
        free_node(head);
    } else
        printf("# invalid line number..\n");
    return 1;
}

// main
int main()
{
    while(draw(read_mode()));
    return 0;
}
