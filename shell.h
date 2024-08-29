#ifndef SHELL_H
#define SHELL_H

/* Standard library headers */
#include <stdio.h>      /* For standard input/output functions */
#include <stdlib.h>     /* For memory allocation, process control, etc. */
#include <string.h>     /* For string manipulation functions */
#include <unistd.h>     /* For POSIX operating system API functions */
#include <sys/types.h>  /* For data types used in system calls */
#include <sys/wait.h>   /* For waiting on child processes */

/* Macro definition */
#define BUFFER_SIZE 1024  /* Define a constant for buffer size */

/* Function prototypes */
void display_prompt(void);                  /* Function to display the shell prompt */
char *read_command(void);                   /* Function to read a command from the user */
int execute_command(char *command);         /* Function to execute the user command */
void handle_error(const char *error_message); /* Function to handle errors (prototype) */

#endif /* SHELL_H */

