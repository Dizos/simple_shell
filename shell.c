#include "shell.h"

/* Read line from stdin*/
char *read_line() {
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

/* Parse the line into arguments*/
char **parse_line(char *line) {
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        fprintf(stderr, "simple_shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\a");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "simple_shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

/* Find the full path of the command*/
char *find_full_path(char *command) {
    char *path = getenv("PATH");
    char *token = strtok(path, ":");
    char full_path[1024];

    while (token != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
        if (access(full_path, X_OK) == 0) {
            return strdup(full_path);
        }
        token = strtok(NULL, ":");
    }
    return NULL;
}

/* Execute the command using execve*/
int execute(char **args) {
    if (args[0] == NULL) {
        /* An empty command was entered*/
        return 1;
    }

    /* Built-in command: exit*/
    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }

    /* Find the full path of the command*/
    char *full_path = find_full_path(args[0]);
    if (full_path == NULL) {
        fprintf(stderr, "simple_shell: command not found: %s\n", args[0]);
        return 1;
    }

    /*Fork process*/
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        /* Child process*/

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
