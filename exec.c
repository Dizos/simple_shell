#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

/**
 * Executes a command using execve.
 * @param cmd The command to execute, including the full path.
 * @param envp Environment variables to pass to execve.
 * @return EXIT_SUCCESS on successful execution, EXIT_FAILURE otherwise.
 */
int execute_command(char *cmd, char **envp) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        char *argv[2] = {cmd, NULL};

        
    if (execve(cmd, argv, envp) == -1) {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
    } 
    	else {
        	do {
            waitpid(pid, &status, WUNTRACED);
        }
       			while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return EXIT_SUCCESS;
}

/**
 * Prints an error message showing the user the command was not found.
 * 
 */
void print_command_not_found_error(char *cmd) {
    fprintf(stderr, "%s: No such file or directory\n", cmd);
}
