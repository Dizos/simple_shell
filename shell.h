#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define BUFFER_SIZE 1024

/* Declare environ */
extern char **environ;

/* Function prototypes */
void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
char *find_command(char *command);

#endif /* SHELL_H */
