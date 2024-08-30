#include "shell.h"

/**
 * main - Entry point of the shell program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	shell_loop();
	return (0);
}
