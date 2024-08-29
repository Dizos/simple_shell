#include "shell.h"

void display_prompt(void)
{
    printf("#cisfun$ ");
    fflush(stdout);
}

char *read_command(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    characters = getline(&buffer, &bufsize, stdin);

    if (characters == -1)
    {
        free(buffer);
        return (NULL);
    }

    if (characters > 0 && buffer[characters - 1] == '\n')
        buffer[characters - 1] = '\0';

    return (buffer);
}
