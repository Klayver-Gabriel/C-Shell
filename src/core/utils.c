#include "../dependency/shell.h"

char *Getcwd(char *buf, size_t size)
{
    if (getcwd(buf, size) == NULL)
    {
        perror("getcwd_error");
        return NULL;
    }
    return buf;
}

char **split_complete_path(char *line){
    char del = '/';
    int count = 0;
    for (int i = 0; line[i] != '\0'; i++){
        if (line[i] == del){
            count++;
        }
    }
    char **path_parts = malloc((count + 1) * sizeof(char *));
    if (path_parts == NULL) {
        perror("malloc_error");
        return NULL;
    }
    int part_index = 0;
    char *start = line;
    for (int i = 0; line[i] != '\0'; i++){
        if (line[i] == del){
            line[i] = '\0';
            path_parts[part_index] = strdup(start);
            if (path_parts[part_index] == NULL) {
                perror("strdup_error");
                // Free previously allocated strings
                for (int j = 0; j < part_index; j++) {
                    free(path_parts[j]);
                }
                free(path_parts);
                return NULL;
            }
            part_index++;
            start = line + i + 1;
        }
    }
    path_parts[part_index] = strdup(start);
    if (path_parts[part_index] == NULL) {
        perror("strdup_error");
        // Free previously allocated strings
        for (int j = 0; j < part_index; j++) {
            free(path_parts[j]);
        }
        free(path_parts);
        return NULL;
    }
    path_parts[part_index + 1] = NULL;
    return path_parts;
}

void *Malloc(size_t size){

    if (size == 0) {
        fprintf(stderr, R "malloc_error: size must be greater than 0\n" RST);
        exit(EXIT_FAILURE);
    }
    void *ptr = malloc(size);
    if (ptr == NULL) {
        perror("malloc_error");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void *Realloc(void *ptr, size_t size){
    if (size == 0) {
        fprintf(stderr, R "realloc_error: size must be greater than 0\n" RST);
        exit(EXIT_FAILURE);
    }
    void *new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        perror("realloc_error");
        free(ptr); 
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

char **split_line(char *line){

    size_t bufsize = BUFSIZ;
    unsigned long position = 0;
    char **tokens = Malloc(bufsize * sizeof *tokens);

    for (char *token = strtok(line, " \t\r\n \v\f"); token != NULL; token = strtok(NULL, "  \t\r\n \v\f")){
        tokens[position++] = token;
        if (position >= bufsize) {
            bufsize *= 2;
            tokens = Realloc(tokens, bufsize * sizeof(char *));
        }
    }
    tokens[position] = NULL;
    return tokens;
}

pid_t	Fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror(R "Fork failed"RST);
		exit(EX_OSERR);
	}
	return (pid);
}

void Execvp(const char *file, char *const argv[])
{
	if (!file || !argv)
	{
		fprintf(stderr, R "Execvp: invalid arguments\n" RST);
		exit(EXIT_FAILURE);
	}
	if (execvp(file, argv) == -1)
	{
		perror(R "Execvp failed" RST);
		exit(EX_UNAVAILABLE);
	}
}


pid_t	Wait(int *status)
{
	pid_t	result;

	if (!status)
	{
		fprintf(stderr, R "Wait: status argument required\n" RST);
		return (-1);
	}
	result = wait(status);
	if (result == -1)
		perror(R "Wait failed" RST);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status); 
	return (result);
}