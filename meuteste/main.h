#ifndef SHELL_H
#define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define Y "\033[1;33m"
# define G "\033[1;32m"
# define R "\033[1;31m"
# define C "\033[1;36m"
# define RST "\033[0m"

void Getcwd(char *, size_t);
#endif
