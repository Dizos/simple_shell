#include "shell.h"

void shell_loop() {
    char *line;
    char **args;
    int status;

    do {
        printf("simple_shell> ");  /*Prompt*/
        line = read_line();        /* Read line*/
        args = parse_line(line);   /* Parse line*/
        status = execute(args);    /* Execute command*/

        free(line);
        free(args);
    } while (status);
}

