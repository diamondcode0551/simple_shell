#include "shell.h"
/**
 * _strdup - duplicates a string
 * @str: string to be duplicated
 * Return: duplicated string
 */
char *_strdup(char *str)
{
	size_t length;
	char *duplicate;

	if (str == NULL)
		return (NULL);
	length = _strlen(str);
	duplicate = malloc(length + 1);

	if (duplicate != NULL)
		_strcpy(duplicate, str);

	return (duplicate);
}
