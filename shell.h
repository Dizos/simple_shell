#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Function prototypes*/
void shell_loop();
char *read_line();
char **parse_line(char *line);
int execute(char **args);
char *find_full_path(char *command);

#endif /* SHELL_H */

