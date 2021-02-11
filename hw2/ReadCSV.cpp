#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int main()
{
    char text[BUFFER_SIZE];
    while(fgets(text, BUFFER_SIZE, stdin))
    {
        text[strlen(text)-1]='\0';
        
        // string token
        char* piece=strtok(text, ",");
        printf("<tr>\n\t");
        while(piece != NULL)
        {
            printf("<td>%s</td>", piece);
            piece = strtok(NULL, ",");
        }
        printf("\n</tr>\n");
    }

    printf("\n");
    return 0;
}