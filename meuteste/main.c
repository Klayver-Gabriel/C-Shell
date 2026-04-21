#include "main.h"


char *shell_read(void){
    char *buf;
    size_t bufsize;

    buf = NULL;

    if(getline(&buf, &bufsize, stdin) == -1){
        if(feof(stdin))
            printf(R "[EOF]\n" RST);
        else
            printf(R "GetLine failed" RST);
        printf("%s\n", buf);
    }
    return buf;
}

int main (int argc, char **argv){

    while (0xCE77){
        printf(" | C-Shell | ");
        char *line = shell_read();
        printf("%s\n", line);
    }

    (void) argc;
    int status = 0;

    // child process
    if (fork() == 0)
        execvp(argv[1], argv + 1);
    wait(status);

    return EXIT_SUCCESS;
}
