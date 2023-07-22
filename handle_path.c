#include "shell.h"
/**
 * handle_path - gets the location of a command
 * @command: shell command
 * Return: path of the command if found, otherwise NULL
 */
char *handle_path(char *command)
{
    struct stat buf;
    char *path, *directory, *path_found, *file_path;
    int dir_size, cmd_size;

    if (command[0] == '/') /* checks for absolute path*/
    {
        if (stat(command, &buf) == 0)
        {
            char *path_found = malloc(_strlen(command) + 1);
            _strcpy(path_found, command);
            return path_found;
        }
        return NULL; /* File not found */
    }
    path = _getenv("PATH");
    if (path == NULL)
        return NULL;
    cmd_size = _strlen(command);
    directory = strtok(path, ":");
    dir_size = _strlen(directory);
    while (directory != NULL)
    {
        file_path = malloc(dir_size + cmd_size + 2);
        _strcpy(file_path, directory);
        _strcat(file_path, "/");
        _strcat(file_path, command);
	if (stat(file_path, &buf) == 0)
        {
            path_found = malloc(_strlen(file_path) + 1);
            _strcpy(path_found, file_path);
            free(file_path);
            return path_found;
        }
        free(file_path);
        directory = strtok(NULL, ":");
    }
    return NULL; /* Command not found in any path */
}
