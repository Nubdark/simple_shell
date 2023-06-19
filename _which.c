#include "shell.h"

/**
 * _which - fills out command by adding it to a matching PATH dir
 * @str: first command user typed into shell ("ls" if user typed "ls -l")
 * @env: envtl variable
 * Return: a copy of filled out command ("/bin/ls" if originally "ls")
 */
char *_which(char *str, list_t *env)
{
	char *pth, *cat = NULL, **toks;
	int i = 0;

	/* get and tokenize PATH directories, then free original str */
	pth = get_env("PATH", env);
	toks = c_str_tok(pth, ":");
	free(pth);

	/* add "/cmd" to each token to see it's recognixed */
	i = 0;
	while (toks[i] != NULL)
	{
		if (toks[i][0] == '\0')
			cat = getcwd(cat, 0);
		else
			cat = _strdup(toks[i]);
		cat = _strcat(cat, "/");
		cat = _strcat(cat, str);
		if (access(cat, F_OK) == 0)
		{
			/* free tokens before returning recognized path */
			free_double_ptr(toks);
			return (cat);
		}
		free(cat); /* free concatenated string if cmd is never found */
		i++;
	}
	free_double_ptr(toks);
	return (str); /* return str if not found; won't pass execve */
}
