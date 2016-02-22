#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    char* str = (char*)calloc(255, sizeof(char));
//    char str[255];

    while(1) {
        printf(" > ");
        fgets(str, 255, stdin);

        if(0 < strlen(str))
            str[strlen(str) - 1] = '\0';

        if(str[0] == '0')
            break;
        printf("length : %d\n", strlen(str));
    }
    free(str);
    return 0;
}
