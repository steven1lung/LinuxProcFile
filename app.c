#include "app.h"

int main()
{
    char input;

    printf("which information do you want?\nVersion(v),CPU(c),Memory(m),Time(t),All(a),Exit(e)?\n");

    if(scanf("%c",&input)!=1) printf("failed to read input\n");


    switch (input)
    {
    case 'a':
    case 'v':
        printf("Version:\n");

        break;
    case 'c':
        printf("CPU:\n");


        break;
    case 'm':
        printf("Memory:\n");


        break;
    case 't':
        printf("Time:\n");


        break;
    default:
        break;
    }


    return 0;
}