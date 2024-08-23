#include "shell.h"

/**
 * user_print - Prints a string to standard output
 * @output: The string to print
 */
void tasam_print(const char *output)
{
	write(STDOUT_FILENO, output, strlen(output));
}