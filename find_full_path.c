#include "shell.h"

char *find_full_path(char *command) {
    char *path = getenv("PATH");
    char *token = strtok(path, ":");
    char full_path[1024];

    while (token != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
        if (access(full_path, X_OK) == 0) {
            return strdup(full_path);
        }
        token = strtok(NULL, ":");
    }
    return NULL;
}
