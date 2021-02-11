#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int main()
{
    printf("<html>\n<body>\n<table border='1'>\n\t<tr>\n\t\t<th>Start</th><th>End</th><th>First</th><th>Middle</th><th>Last</th>\n\t</tr>\n");
    char text[BUFFER_SIZE];
    while(fgets(text, BUFFER_SIZE, stdin))
    {
        // resolves '\n' issue
        text[strlen(text)-1]='\0';
        printf("\t%s\n",text);
    }
    printf("</table>\n</body>\n</html>");
    return 0;
}