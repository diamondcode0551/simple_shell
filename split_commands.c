#include "shell.h"
/**
 * split_commands - tokenizes a string
 * @input: string to tokenize
 * @arguments: commands
 * Return: void
 */
void split_commands(char *input, char **arguments)
{
	char *start = input;
	char *end = input;

	while (*end != '\0')
	{
		if (*end == ';')
		{
			*end = '\0';
			execute_command(start, arguments);
			*end = ';';
			start = end + 1;
		}
		end++;
	}
	if (*start != '\0')
		execute_command(start, arguments);
}
/**
 * execute_command - executes a single command
 * @command: command to be executed
 * @arguments: arg
 * Return: void
 */
void execute_command(char *command, char **arguments)
{
	char *end;

	while (*command && (*command == ' ' || *command == '\t'))
		command++;
	end = command + _strlen(command) - 1;
	while (end > command && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	*(end + 1) = '\0';
	if (*command != '\0')
	{
		arguments = get_tokens(command, _strlen(command), arguments);
		execute_commands(arguments);
	}
}
