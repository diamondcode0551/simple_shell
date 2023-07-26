#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

extern char **environ;
#define BUFFER_SIZE 1024

/* basic custom library function prototypes */
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(const char *s1, const char *s2);
int _atoi(char *s);

/* handling path and tokenization prototypes */
char **get_tokens(char *input, ssize_t bytes_read, char **arguments);
char *handle_path(char *command);

/**
 *struct builtins - stores builtin command and its function
 *@name: name of builtin command
 *@function: buitlin function
 */
typedef struct builtins
{
	const char *name;
	int (*function)(char **arguments);
} builtin_command;

/* Function prototypes for built-in commands */
int exit_builtin(char **arguments);
int cd_builtin(char **arguments);
int help_builtin(char **arguments);
int env_builtin(char **arguments);
int execute_commands(char **arguments);
int launch(char **arguments);

/**
 * struct mybuiltin - Pointer for buildin function
 * @arguments: Command
 * @functions: Execute command
 */
typedef struct mybuiltin
{
	char *arguments;
	void (*functions)(char **);
} mybuiltin;

/* Environment help */
int _putchar(char c);
void _puts(char *str);
char *_getenv(const char *var);
char *_concats(char *first, char *second, char *third);

/* custom_library_functions */
ssize_t _getline(char **input);

void split_commands(char *input, char **arguments);
void execute_command(char *command, char **arguments);
char *_strdup(char *str);

#endif
