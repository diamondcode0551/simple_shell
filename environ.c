#include "shell.h"
/**
 * _setenv - sets the value of environment variable
 * @name: name of the environment variable
 * @value: value to set
 * @overwrite: flag to indicatewhether to overwrite if variable exists
 * Return: 0 success, -1 failure
 */
int _setenv(char *name, char *value, int overwrite)
{
	EnvVarNode *node, *new_node;
	EnvVarNode *env_head = NULL;

	if (name == NULL)
		return (-1);
	for (node = env_head; node != NULL; node = node->next)
	{
		if (_strcmp(node->name, name) == 0)
		{
			if (!overwrite)
				return (0);
			free(node->value);
			node->value = _strdup(value);
			if (node->value == NULL)
				return (-1);
			return (0);
		}
	}
	new_node = malloc(sizeof(EnvVarNode));

	if (new_node == NULL)
		return (-1);
	new_node->name = _strdup(name);
	new_node->value = _strdup(value);
	if (new_node->name == NULL || new_node->value == NULL)
	{
		free(new_node->name);
		free(new_node->value);
		free(new_node);
		return (-1);
	}
	new_node->next = env_head;
	env_head = new_node;
	return (0);
}
