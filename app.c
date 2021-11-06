#include "app.h"

int main()
{
    char input;
    FILE *fp;
    char dump;
    while(1)
    {
        fp=fopen("/proc/my_info","r");
        printf("which information do you want?\nVersion(v),CPU(c),Memory(m),Time(t),All(a),Exit(e)?");


        scanf("%c%*c",&input);
        printf("\n");
        int i;
        if(input=='e')
        {
            fclose(fp);
            return 0;
        }
        char s;
        switch (input)
        {
        case 'a':
            while((s=fgetc(fp))!=EOF)
            {
                printf("%c",s);
            }
            break;
        case 'v':
            while((s=fgetc(fp))!='\n')
            {
                printf("%c",s);
            }
            printf("\n");
            while((s=fgetc(fp))!='\n')
            {
                printf("%c",s);
            }
            printf("\n\n");
            break;
        case 'c':
            for(i=0; i<3; i++)
            {
                while((s=fgetc(fp))!='\n');
            }

            while((s=fgetc(fp))!='\n')
            {
                printf("%c",s);

            }
            printf("\n");


            while((s=fgetc(fp))!='=')
            {
                printf("%c",s);

            }
            printf("\n");

            break;
        case 'm':
            for(i=0; i<4; i++)
            {
                while((s=fgetc(fp))=='=');
                while((s=fgetc(fp))!='=');
            }
            for(i=0; i<13; i++)
            {
                while((s=fgetc(fp))!='\n')
                {
                    printf("%c",s);

                }
                printf("\n");
            }

            printf("\n");
            break;
        case 't':
            for(i=0; i<6; i++)
            {
                while((s=fgetc(fp))=='=');
                while((s=fgetc(fp))!='=');
            }
            for(i=0; i<3; i++)
            {
                while((s=fgetc(fp))!='\n')
                {
                    printf("%c",s);

                }
                printf("\n");
            }
            printf("\n");

            break;
        default:
            break;
        }


    }


    fclose(fp);
    return 0;
}