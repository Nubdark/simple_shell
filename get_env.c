#include "shell.h"

/**
 * c_strdup - custom string duplicates; excludes beginning bytes
 * @str: string to duplicate (envtl variable PATH=/bin:/bin/ls)
 * @cs: no of bytes to exclude (excludes "PATH=")
 * Return: string (e.g. /bin:/bin/ls)
 */
char *c_strdup(char *str, int cs)
{
	char *duplicate_str;
	int i, len = 0;

	if (str == NULL) /* validates str input */
		return (NULL);

	/* calculates len + null that terminates at malloc */
	while (*(str + len))
		len++;
	len++;

	/* allocates memory but exclude envtl variable title (PATH) */
	duplicate_str = malloc(sizeof(char) * (len - cs));
	if (duplicate_str == NULL)
		return (NULL);

	i = 0;
	while (i < (len - cs))
	{
		*(duplicate_str + i) = *(str + cs + i);
		i++;
	}
	return (duplicate_str);
}

/**
 * get_env - finds and returns a copy of the requested envtl variable
 * @str: string to store it in
 * @env: entire set of envtl variables
 * Return: copy of requested envtl variable
 */
char *get_env(char *str, list_t *env)
{
	int j = 0, cs = 0;

	while (env != NULL)
	{
		j = 0;
		while ((env->var)[j] == str[j]) /* find desired env variable */
			j++;
		if (str[j] == '\0' && (env->var)[j] == '=')
			break;
		env = env->next;
	}

	while (str[cs] != '\0') /* find how many bytes in env variable title */
		cs++;
	cs++; /*counts 1 more for = sign*/
	return (c_strdup(env->var, cs)); /* make a copy of variable without title */
}
