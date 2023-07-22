#include "shell.h"
/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately
 */

int _putchar(char c)

{
		return (write(1, &c, 1));
}

/**
 * _puts - print a string
 * @str: string type
 */

void _puts(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
	_putchar('\n');
}

/**
 * _getenv - Gets value of variable
 * @var: Name of var
 * Return: string
 */

char *_getenv(const char *var)
{
	int i;
	int j;
	char *val;

	if (!var)
		return (NULL);
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (var[j] == environ[i][j])
		{
			while (var[j])
			{
				if (var[j] != environ[i][j])
					break;
				j++;
			}
			if (var[j] == '\0')
			{
				val = (environ[i] + j + 1);
				return (val);
			}
		}
	}
	return (0);
}

/**
 * _concats - Concatenates 3 strings
 * @first: first string
 * @second: second string
 * @third: third string
 * Return: Pointer
 */

char *_concats(char *first, char *second, char *third)
{
	char *value;
	int a, b, c, i, j;

	a = _strlen(first);
	b = _strlen(second);
	c = _strlen(third);

	value = malloc(a + b + c + 1);
	if (!value)
		return (NULL);

	for (i = 0; first[i]; i++)
		value[i] = first[i];
	j = i;

	for (i = 0; second[i]; i++)
		value[j + i] = second[i];
	j = j + i;

	for (i = 0; third[i]; i++)
		value[j + i] = third[i];
	j = j + i;

	value[j] = '\0';

	return (value);
}


