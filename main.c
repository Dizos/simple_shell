#include "shell.h"

int main(void)
{
    char *command;

    while (1)
    {
        display_prompt();
        command = read_command();

        if (command == NULL)
        {
            printf("\n");
            break;
        }

        if (execute_command(command) == -1)
        {
            break;
        }

        free(command);
    }

    return (0);
}
