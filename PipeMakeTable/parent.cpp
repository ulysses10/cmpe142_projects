#include "globals.hpp"

void parent(int fd[])
{
    string prefix = "\t<tr>\n\t\t<td>";
    string divider = "</td><td>";
    string postfix = "</td>\n\t</tr>\n";
    
    // Close the unused READ end of the pipe.
    close(fd[READ_END]);

    // Read from console in and Write HTML body to the pipe.
    for(string text; getline(cin,text);)
    {
        int n=text.length();
        write(fd[WRITE_END], prefix.c_str(), prefix.length());

        for(int i=0; i<n; i++)
        {
            while(text[i]==',')
            {
                i++;
                write(fd[WRITE_END], divider.c_str(), divider.length());
            }
            write(fd[WRITE_END], text.c_str()+i, 1);
        }

        write(fd[WRITE_END], postfix.c_str(), postfix.length());
    }
    // --Close WRITE end of pipe after done writing     
    close(fd[WRITE_END]);
}