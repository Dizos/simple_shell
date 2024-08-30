#include "shell.h"

/**
 * shell_loop - The main loop reads, parses, and executes commands
 */

void shell_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		line = read_line();
		if (!line)
			break;
		args = parse_line(line);
		status = execute(args);

		free(line);
		free(args);
	} while (status);
}
