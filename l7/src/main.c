/**
 * CL5 - lesson 7
 *
 * main.c
 *
 * @author ashon
 * @date 2014-04-15
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/*
 * draw shapes.
 */
int draw(ULL mode, ULL lines)
{
    ULL i, j;

    cmd_node* head;
    cmd_node* cur;

    void(*loop)(ULL, cmd_node*) = 0;

    if(mode == 0)
        return 1;

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
