#include "shell.h"

/* Function to execute a command using fork and execve */
int execute_command(char *command)
{
    pid_t pid;              /* Variable to hold the process ID */
    char *argv[2];          /* Array to hold the command and NULL terminator */
    extern char **environ;  /* External variable for the environment */

    pid = fork();           /* Create a new process by forking */

    /* Check if fork failed */
    if (pid == -1)
    {
        perror("Error:");   /* Print an error message if fork fails */
        return (-1);        /* Return -1 to indicate failure */
    }

    /* Child process executes this block */
    if (pid == 0)
    {
        argv[0] = command;  /* Assign the command to the first element of argv */
        argv[1] = NULL;     /* NULL terminate the argument list */

        /* Execute the command using execve */
        if (execve(command, argv, environ) == -1)
        {
            printf("./shell: No such file or directory\n");  /* Error message if execve fails */
            exit(1);         /* Exit the child process with status 1 */
        }
    }
    else
    {
        wait(NULL);         /* Parent process waits for the child process to finish */
    }

    return (0);             /* Return 0 to indicate success */
}
