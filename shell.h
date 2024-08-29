#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void display_prompt(void);
char *read_command(void);
int execute_command(char *command);
void handle_error(const char *error_message);

#endif /* SHELL_H */
