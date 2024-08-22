#include "shell.h"

/**
 * execute_command - Forks a child process to execute a command
 * @command: The command to be executed
 *
 * Return: void
 */
void execute_command(const char *command)
{
	pid_t child_pid = fork(); /* Creates a child process */

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0) /* Child process */
	{
		execve(command, command, (char *)NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else /* Parent process */
	{
		wait(NULL);
	}
}