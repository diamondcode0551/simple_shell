#include "shell.h"
/**
 * exit_builtin - exit the shell when invoked
 * @arguments: commands
 * Return: exit status
 */
int exit_builtin(char **arguments)
{
	int exit_code;
	char *error_message;

	if (arguments[0] != NULL && strcmp(arguments[0], "exit") == 0)
	{
		if (arguments[1] != NULL)
		{
			exit_code = _atoi(arguments[1]);
			if (exit_code != 0 || arguments[1][0] == '0')
				exit(exit_code);
			else
				exit(1);
		}
		else
			exit(0);
	}
	error_message = "shell: command not found\n";
	write(2, error_message, strlen(error_message));

	return (1);
}
/**
 * env_builtin - displays the environment
 * @arguments: commands
 * Return: 1 otherwise 0
 */
int env_builtin(char **arguments)
{
	int i;

	(void)arguments;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	return (-1);
}

/**
 * help_builtin - displays help
 * @arguments: commands
 * Return: 1 otherwise 0
 */
int help_builtin(char **arguments)
{
	char *info = "\n\n\t\t\tWelcome to the help page.\n";

	(void)arguments;

	write(STDOUT_FILENO, info, _strlen(info));
	info = "\nThe following are the builtin commands in this shell.\n";
	write(STDOUT_FILENO, info, _strlen(info));
	info = "\n\t\t cd \t env \t help \t exit \n";
	write(STDOUT_FILENO, info, _strlen(info));
	info = "\n\t1. To navigate throught the directories  use the 'cd' command.\n";
	write(STDOUT_FILENO, info, _strlen(info));
	info = "\t2. TO exit shell use the 'exit' command.\n";
	write(STDOUT_FILENO, info, _strlen(info));
	info = "\t3. For help type 'help' command.\n\n";
	write(STDOUT_FILENO, info, _strlen(info));

	return (1);
}




/**
 * cd_builtin - changes directory when invoked
 * @arguments: commands
 * Return: 1 if successful, otherwise 0
 */
int cd_builtin(char **arguments)
{
	char prev_dir[1024];
	char *home_dir, *info;

	if (!arguments[1] || _strcmp(arguments[1], "~") == 0)
	{
		home_dir = _getenv("HOME");
		if (!home_dir)
		{
			write(STDERR_FILENO, "cd: No HOME directory found.\n", 29);
			return (0);
		}
		arguments[1] = home_dir;
	}
	if (_strcmp(arguments[1], "-") == 0)
	{
		info = _getenv("OLDPWD");
		if (!info)
		{
			write(STDERR_FILENO, "cd: OLDPWD not set.\n", 20);
			return (0);
		}
		write(STDOUT_FILENO, info, _strlen(info));
		write(STDOUT_FILENO, "\n", 1);
		if (chdir(info) != 0 || !getcwd(prev_dir, sizeof(prev_dir)))
		{
			perror("chdir");
			return (0);
		}
	}
	else
	{
		if (!getcwd(prev_dir, sizeof(prev_dir)) || chdir(arguments[1]) != 0)
		{
			perror("cd");
			return (0);
		}
		setenv("OLDPWD", prev_dir, 1);
	}
	setenv("PWD", arguments[1], 1);
	return (1);
}


/**
 * execute_commands - executes commands passed through it
 * @arguments: commands
 * Return: 1
 */
int execute_commands(char **arguments)
{
	int i = 0;
	builtin_command builtins[] = {
		{"exit", exit_builtin},
		{"cd", cd_builtin},
		{"env", env_builtin},
		{"help", help_builtin}
	};

	if (arguments[0] == NULL)
		return (1);
	while (i < 4)
	{
		if (_strcmp(arguments[0], builtins[i].name) == 0)
			return (builtins[i].function(arguments));
		i++;
	}

	return (launch(arguments));
}

