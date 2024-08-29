#include "shell.h"

int launch(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execve(args[0], args, environ) == -1)
        {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        /* Error forking */
        perror("shell");
    }
    else
    {
        /* Parent process */
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/* Add any other functions from shell.c here */
