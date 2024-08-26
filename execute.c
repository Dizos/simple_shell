#include "shell.h"

/**
 * execute - Executes a command.
 * @args: The arguments to execute.
 *
 * Return: 1 if the shell should continue, 0 if it should exit.
 */
int execute(char **args)
{
	pid_t pid;
	int status;
	char *command_path;

	if (args[0] == NULL)
		return (1);

	if (strcmp(args[0], "exit") == 0)
		return (0);

	command_path = find_command(args[0]);
	if (command_path == NULL)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(command_path, args, environ) == -1)
		{
			perror("hsh");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("hsh");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	free(command_path);
	return (1);
}
