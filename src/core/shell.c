#include "../dependency/shell.h"

t_buildin g_builtins[] = {
    // {"cd", shell_cd},
    // {"help", shell_help},
    {"exit", shell_exit},
    {NULL, NULL}
};

int status = 0;

void shell_launch(char **args){
    if(Fork() == CHILD){
        Execvp(args[0], args);
    }
    else{
        Wait(&status);
    }
}

char *shell_read()
{
    char *line = NULL;
    size_t buffer_size;
    char cwd[BUFSIZ];

    Getcwd(cwd, sizeof(cwd));
    printf(C "in %s  " RST "λ ", cwd);

    if (getline(&line, &buffer_size, stdin) == -1)
    {   
        free(line);
        line = NULL;
        if (feof(stdin))
            printf(R "[EOF]\n" RST);
        else
        printf(R "getline_error" RST);
        
    }
    return line;
}

void shell_exec(char **args){
    if (!args || !args[0])
        return;
    int i = 0;
    const char *curr;
    while((curr = g_builtins[i].name)){
        if (strcmp(curr, args[0]) == 0){
            status = g_builtins[i].function(args);
            return;
        }
        i++;
    }

    shell_launch(args);
}

int main()
{
    char *line;
    char **args;
    char * user = getenv("USER");


    while (0xCE77)
    {
        printf("🃏%s ", user);
        line = shell_read();

        if (line == NULL) 
            continue;
        
        args = split_line(line);

        if (args == NULL) {
            free(line);
            continue;
        }

        shell_exec(args);

        
        free(line);
        free(args);        
    }
}