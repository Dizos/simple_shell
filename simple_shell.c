#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Function prototypes */
void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
char *find_full_path(char *command);

/**
 * main - Entry point of the shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success.
 */
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	shell_loop();
	return (0);
}

/**
 * shell_loop - The main loop that reads, parses, and executes commands.
 */
void shell_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("simple_shell> "); /* Prompt */
		line = read_line();   /* Read line */
		args = parse_line(line);  /* Parse line */
		status = execute(args);   /* Execute command */

		free(line);
		free(args);
	} while (status);
}

/**
 * read_line - Reads a line from stdin.
 *
 * Return: The line read.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	getline(&line, &bufsize, stdin);
	return (line);
}

/**
 * parse_line - Parses the line into arguments.
 * @line: The line to parse.
 *
 * Return: An array of arguments.
 */
char **parse_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "simple_shell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "simple_shell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * find_full_path - Finds the full path of a command.
 * @command: The command to find.
 *
 * Return: The full path of the command, or NULL if not found.
 */
char *find_full_path(char *command)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");
	char full_path[1024];

	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
		{
			return (strdup(full_path));
		}
		token = strtok(NULL, ":");
	}
	return (NULL);
}

/**
 * execute - Executes a command using execve.
 * @args: The arguments to execute.
 *
 * Return: 1 if the shell should continue, 0 if it should exit.
 */
int execute(char **args)
{
	pid_t pid, wpid;
	int status;
	char *full_path;

	if (args[0] == NULL)
	{
		/* An empty command was entered */
		return (1);
	}

	if (strcmp(args[0], "exit") == 0)
	{
		return (0);
	}

	full_path = find_full_path(args[0]);
	if (full_path == NULL)
	{
		fprintf(stderr, "simple_shell: command not found: %s\n", args[0]);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execve(full_path, args, NULL) == -1)
		{
			perror("simple_shell");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		/* Error forking */
		perror("simple_shell");
	}
	else
	{
		/* Parent process */
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	free(full_path);
	return (1);
}

