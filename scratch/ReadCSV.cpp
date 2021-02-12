#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int main()
{
    char text[BUFFER_SIZE];
    while(fgets(text, BUFFER_SIZE, stdin))
    {
        // resolves '\n' issue
        text[strlen(text)-1]='\0';

        // string token
        char* piece=strtok(text, ",");
        printf("<tr>\n\t");
        while(piece != NULL)
        {

            if(*piece)
                printf("<td>%s</td>", piece);
            else
                printf(" ");
            piece = strtok(NULL, ",");
            //fflush(stdout);
        }
        printf("\n</tr>\n");
    }

    printf("\n");
    return 0;
}