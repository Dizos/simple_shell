#include "shell.h"

int _eputchar(char c)
{
	return write(2, &c, 1);
}