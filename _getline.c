#include "shell.h"
/**
 * _getline - custom implementation of the getline function
 * @input: pointer to store the read line
 * Return: number of bytes read, or -1 on failure
 */
ssize_t _getline(char **input)
{
	static char buffer[BUFFER_SIZE];
	static ssize_t buffer_pos = 0, bytes_in_buffer = 0;
	ssize_t bytes_read = 0, newline_pos = -1;

	if (!input)
		return -1;

	if (buffer_pos >= bytes_in_buffer) /* Refill buffer if it's empty or at the end */
	{
		bytes_in_buffer = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		buffer_pos = 0;

		if (bytes_in_buffer <= 0)
			return -1; /* Reached EOF or an error occurred */
	}
	while (buffer_pos + bytes_read < bytes_in_buffer)/* Find the position of the newline character */
	{
		if (buffer[buffer_pos + bytes_read] == '\n')
		{
			newline_pos = buffer_pos + bytes_read;
			break;
		}
		bytes_read++;
	}
	if (newline_pos == -1) /* Newline not found in the current buffer, read more */
	{
		bytes_read = bytes_in_buffer - buffer_pos;
		newline_pos = bytes_in_buffer;
	}
	*input = malloc(newline_pos + 1);/* Allocate memory for the line */
	if (!*input)
		return -1; /* Allocation error */
	for (ssize_t i = 0; i < newline_pos; i++)/* Copy the data from the buffer into the line */
		(*input)[i] = buffer[buffer_pos + i];
	(*input)[newline_pos] = '\0'; /* Null-terminate the line */
	buffer_pos += bytes_read + 1; /* Move buffer_pos to the next character after newline */
	return newline_pos;
}
