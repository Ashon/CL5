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

#define ULL unsigned long long

int main()
{
    ULL mode;
    ULL lines;
    printf("asdf");
    while(1) {
        // read draw mode
        mode = read_mode();

        if(mode) {
            // read lines
            lines = read_lines(mode);

            // draw pattern
            draw(mode, lines);
        }
    }
    return 0;
}
