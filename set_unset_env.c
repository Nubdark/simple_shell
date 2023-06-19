#include "shell.h"

/**
 * find_env - find given envtl variable in linked list
 * @env: envtl variable linked list
 * @str: variable name
 * Return: idx of node in linked list
 */
int find_env(list_t *env, char *str)
{
	int j = 0, index = 0;

	while (env != NULL)
	{
		j = 0;
		while ((env->var)[j] == str[j]) /* find desired env variable */
			j++;
		if (str[j] == '\0')
		       	/* if matches compltely then break, return index */
			break;
		env = env->next;
		index++;
	}
	if (env == NULL)
		return (-1);
	return (index);
}

/**
 * _unsetenv - removes node in envtl linked list
 * @env: linked list
 * @str: user's typed in command (e.g. "unsetenv MAIL")
 * Return: 0 on success
 */
int _unsetenv(list_t **env, char **str)
{
	int index = 0, j = 0;

	if (str[1] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		free_double_ptr(str);
		return (-1);
	}
	index = find_env(*env, str[1]); /* get index of node to delete */
	free_double_ptr(str);
	if (index == -1) /* check if index has error */
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	j = delete_nodeint_at_index(env, index); 
	if (j == -1)
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	return (0);
}

/**
 * _setenv - create or modify existing envtl variable in linked list
 * @env: linked list
 * @str: user's typed in command like using setenv
 * Return: 0 on success, 1 on err
 */
int _setenv(list_t **env, char **str)
{
	int index = 0, j = 0;
	char *cat;
	list_t *holder;

	if (str[1] == NULL || str[2] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		free_double_ptr(str);
		return (-1);
	}
	cat = _strdup(str[1]); /* concatenate strings to be new node data */
	cat = _strcat(cat, "=");
	cat = _strcat(cat, str[2]);
	index = find_env(*env, str[1]); /* find index to traverse to node */
	if (index == -1)
	{
		add_end_node(env, cat); /* if not there create env var */
	}
	else
	{
		holder = *env;
		while (j < index)
		{
			holder = holder->next;
			j++;
		}
		free(holder->var); /* else free malloced data */
		holder->var = _strdup(cat); /* assigns to new malloced data */
	}
	free(cat);
	free_double_ptr(str);
	return (0);
}
