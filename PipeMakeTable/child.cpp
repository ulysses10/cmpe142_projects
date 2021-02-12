#include "globals.hpp"

void child(int fd[])
{

    // printf("<html>\n<body>\n<table border='1'>\n\t<tr>\n\t\t<th>Start</th><th>End</th><th>First</th><th>Middle</th><th>Last</th>\n\t</tr>\n");
    // char text[BUFFER_SIZE];
    // while(fgets(text, BUFFER_SIZE, stdin))
    // {
    //     // resolves '\n' issue
    //     text[strlen(text)-1]='\0';
    //     printf("\t%s\n",text);
    // }
    // printf("</table>\n</body>\n</html>");

    char buffer[BUFFER_SIZE];

    // Close the unused WRITE end of the pipe.
    close(fd[WRITE_END]);

    // Read from the READ end of the pipe.
    ssize_t size;
    printf("<html>\n<body>\n<table border='1'>\n\t<tr>\n\t\t<th>Start</th><th>End</th><th>First</th><th>Middle</th><th>Last</th>\n\t</tr>\n");

    for (;;)
    {
        size = read(fd[READ_END], buffer, BUFFER_SIZE);
        if (size <= 0) break;

        if (size < BUFFER_SIZE) buffer[size] = '\0';
        printf("%s", buffer);
    }
    printf("</table>\n</body>\n</html>");

    // Close the READ end of the pipe.
    close(fd[READ_END]);

}
