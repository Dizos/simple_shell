#include "shell.h"

/**
 * read_command - Reads a command from standard input
 * @command: The buffer to store the command
 * @size: The size of the buffer
 */
void read_command(char *command, size_t size)
{
	if (fgets(command, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			tasam_print("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			tasam_print("Error while reading input.\n");
			exit(EXIT_FAILURE);
		}
	}

	command[strcspn(command, "\n")] = '\0'; /* Remove newline */
}