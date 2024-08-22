#include "shell.h"

void _eputs(char *str)
{
	if (str)
		while (*str)
			_eputchar(*str++);
}