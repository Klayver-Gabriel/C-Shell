#include "shell.h"

char *shell_read()
{
    char *line = NULL;
    size_t buffer_size;
    char cwd[BUFSIZ];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd_error");
        return NULL;
    }

    printf(C ":) %s (:" RST "$> ", cwd);
    if (getline(&line, &buffer_size, stdin) == -1)
    {   
        line = NULL;
        if (feof(stdin))
            printf(R "[EOF]\n" RST);
        else
        printf(R "getline_error" RST);
        
    }
    return line;
}



int main(int argument, char **variables)
{
    char *line;
    // ... rest of the code

    while (1)
    {
        printf(" | C-Shell | ");
        line = shell_read();
        printf("%s\n",line);
        
        // ... rest of the code
    }
}