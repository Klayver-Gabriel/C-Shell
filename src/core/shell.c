#include "dependency/shell.h"

char *shell_read()
{
    char *line = NULL;
    size_t buffer_size = NULL;
    if (getline(&line, &buffer_size, stdin) == -1)
    {
        if (feof(stdin))
        {
            print(f"C-Shell: EOF received, exiting...\n"););
        }
        else
        {
            perror("C-Shell: getline");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}



int main(int argument, char **variables)
{
    char *line;
    // ... rest of the code

    while (1)
    {
        printf("C-Shell> ");
        line = shell_read
        line = NULL;
        size_t buffer_size = 0;
        
        // ... rest of the code
    }
}