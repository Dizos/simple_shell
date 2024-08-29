#include "shell.h"

/* error essage*/
void handle_error(const char *error_message)
{
    perror(error_message);
}
