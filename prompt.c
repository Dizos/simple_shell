#include "shell.h"

/* Function to display the shell prompt */
void display_prompt(void)
{
    printf("#cisfun$ ");  /* Print the shell prompt */
    fflush(stdout);  /* Flush the output buffer to ensure the prompt is displayed immediately */
}

/* Function to read the command input by the user */
char *read_command(void)
{
    char *buffer = NULL;  /* Pointer to hold the command input by the user */
    size_t bufsize = 0;   /* Variable to hold the size of the buffer */
    ssize_t characters;   /* Variable to hold the number of characters read */

    /* Read the input line from the user */
    characters = getline(&buffer, &bufsize, stdin);

    /* Check if reading the input failed (e.g., EOF or error) */
    if (characters == -1)
    {
        free(buffer);  /* Free the memory allocated for the buffer */
        return (NULL);  /* Return NULL to indicate an error or EOF */
    }

    /* Remove the newline character from the end of the input, if present */
    if (characters > 0 && buffer[characters - 1] == '\n')
        buffer[characters - 1] = '\0';

    return (buffer);  /* Return the buffer containing the command */
}
