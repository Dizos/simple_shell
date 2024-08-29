#include "shell.h"

int execute_command(char *command)
{
    pid_t pid;
    char *argv[2];
    extern char **environ;

    pid = fork();

    if (pid == -1)
    {
        perror("Error:");
        return (-1);
    }

    if (pid == 0)
    {
        argv[0] = command;
        argv[1] = NULL;
        if (execve(command, argv, environ) == -1)
        {
            printf("./shell: No such file or directory\n");
            exit(1);
        }
    }
    else
    {
        wait(NULL);
    }

    return (0);
}
