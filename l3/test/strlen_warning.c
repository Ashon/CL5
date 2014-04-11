#include <stdio.h>
#include <string.h>

int main(){
    char source[] = "source";
    char target[255];
    int i;
/*
    for(i = 0; i < 3; i++)
        target[i] = source[i];

    printf("\nwarning..\n");
    printf("string : %s\n", target);
    printf("length : %u\n", (unsigned)strlen(target));

    target[3] = '\0';
    */

    fgets(target, 255, stdin);
    target[strlen(target) - 1] = '\0';
    

    printf("\nno warning..\n");
    target[0] = '\0';
    strlen(target);
    /*
    printf("string : %s\n", target);
    printf("length : %u\n", (unsigned)strlen(target));
*/
   return 0;
}
