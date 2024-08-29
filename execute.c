#include "shell.h"

int execute(char **args) {
    if (args[0] == NULL) {
        /* An empty command was entered*/
        return 1;
    }

    /*Built-in command: exit*/
    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }

    /* Find the full path of the command*/
    char *full_path = find_full_path(args[0]);
    if (full_path == NULL) {
        fprintf(stderr, "simple_shell: command not found: %s\n", args[0]);
        return 1;
    }

    /* Fork process*/
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        /*Child process*/

        /* Using execve instead of execvp*/
        if (execve(full_path, args, NULL) == -1) {
            perror("simple_shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Error forking*/
        perror("simple_shell");
    } else {
        /* Parent process*/
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    free(full_path);
    return 1;
}

