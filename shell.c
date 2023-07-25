#include "shell.h"
/**
 *main - executes the shell process
 *@ac: argument count
 *@argv: argument variables
 *Return: 0
 */
int main(int ac, char **argv)
{
	ssize_t bytes_read;
	char **arguments;
	char *input, *prompt, *input_copy;

	(void)ac;
	input = NULL;
	prompt = ">>>$ ";
	arguments = argv;

	while (1) /* prompt loop*/
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));

		bytes_read = _getline(&input);

		if (bytes_read == -1)/* checks if reached EOF or CTRL + D is pressed */
			break;
		input_copy = _strdup(input);
		if (input_copy == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		split_commands(input_copy, arguments);
		free(input_copy);
	}
	free(input);


	return (0);
}


/**
 * launch - creates a child process to execute the command
 * @arguments: commands to be executed
 * Return: 1
*/
int launch(char **arguments)
{
	pid_t pid;
	int state;
	char *path = NULL;
	char *command = NULL;
	char *error;

	pid = fork();
	if (pid == 0)
	{
		if (arguments)
		{
			path = arguments[0];
			command = handle_path(path);

			/*executes command using execve function*/
			if (execve(command, arguments, NULL) == -1)
			{
				error = "./shell: No such file or directory";
				write(STDOUT_FILENO, error, _strlen(error));
				write(STDOUT_FILENO, "\n", 1);
				exit(EXIT_FAILURE);
			}
		}
	}
	else if (pid < 0)
	{
		perror("Folk Error");
	}
	else
	{
		return (waitpid(pid, &state, 0));
	}

	return (1);
}


