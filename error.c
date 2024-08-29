#include "shell.h"

void handle_error(const char *error_message)
{
    perror(error_message);
}
