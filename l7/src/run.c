/**
 * CL5 - lesson 7
 *
 * run.c
 *
 * @author ashon
 * @date 2014-04-15
 *
 */
#include <stdio.h>

#define MAX_LINE 100
#define ULL unsigned long long
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
}

int main() {
    ULL mode;
    ULL lines;

    while(1){
        mode = read_mode();
        if(mode){
            lines = read_lines(mode);
            draw(mode, lines);
        }
    }
    return 0;
}
