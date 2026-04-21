#ifndef SHELL_H
#define SHELL_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sysexits.h>

# define Y "\033[1;33m"
# define G "\033[1;32m"
# define R "\033[1;31m"
# define C "\033[1;36m"
# define RST "\033[0m"

#define CHILD 0

typedef struct s_builtin{
    char *name;
    int (*function)(char **args);
} t_buildin;

// int shell_cd(char **args);
// int shell_help(char **args);
int shell_exit(char **args);

char *Getcwd(char *, size_t);
char **split_complete_path(char *line);
char **split_line(char *line);
void *Malloc(size_t size);
pid_t Fork(void);
void Execvp(const char *file, char *const argv[]);
pid_t	Wait(int *status);

#endif