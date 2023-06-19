#include "shell.h"

/**
 * env_linked_list - creates a linked list from envtl variables
 * @env: envtl variables
 * Return: linked list
 */
list_t *env_linked_list(char **env)
{
	list_t *head;
	int i = 0;

	head = NULL;
	while (env[i] != NULL)
	{
		add_end_node(&head, env[i]);
		i++;
	}
	return (head);
}

/**
 * _env - prints envtl variables
 * @str: user's command into shell (i.e. "env")
 * @env: envtl variables
 * Return: 0 on success
 */
int _env(char **str, list_t *env)
{
	free_double_ptr(str); /* frees user input */
	print_list(env); /* prints env */
	return (0);
}
