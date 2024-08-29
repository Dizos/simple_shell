#include "shell.h"

/* Main function that runs the shell loop */
int main(void)
{
    char *command;  /* Pointer to hold the command entered by the user */

    /* Infinite loop to continuously display the prompt and execute commands */
    while (1)
    {
        display_prompt();  /* Function to display the shell prompt */
        command = read_command();  /* Function to read the command input by the user */

        /* Check if the user input is NULL (e.g., EOF or empty command) */
        if (command == NULL)
        {
            printf("\n");  /* Print a newline character */
            break;  /* Exit the loop and terminate the shell */
        }

        /* Execute the command and check if there was an error */
        if (execute_command(command) == -1)
        {
            free(command);  /* Free the memory allocated for the command */
            break;  /* Exit the loop and terminate the shell */
        }

        free(command);  /* Free the memory allocated for the command after execution */
    }

    return (0);  /* Return 0 to indicate successful termination of the program */
}
