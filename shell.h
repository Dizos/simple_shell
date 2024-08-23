#ifndef SHELL_H
#define SHELL_H

/* Header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

/* Function prototypes */
void display_prompt(void);
void tasam_print(const char *output);
void read_command(char *command, size_t size);
void execute_command(const char *command);

#endif /* SHELL_H */