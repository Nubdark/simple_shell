#include "shell.h"

/**
 * ctrl_c - ignores command Ctrl-C input and prints prompt again
 * @n: takes in int from signal
 */
void ctrl_c(int n)
{
	(void)n;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * built_in - handles builtins (exit, env, cd)
 * @token: user's typed command
 * @env: envtl variable
 * @num: take in user command typed to write error message
 * @command: brings in command to free
 * Return: 1 if acted on builtin, 0 if not
 */
int built_in(char **token, list_t *env, int num, char **command)
{
	int i = 0;

	/* if user types "exit" frees cmd tokens, and exits */
	if (_strcmp(token[0], "exit") == 0)
	{
		i = __exit(token, env, num, command);
	}
	/* if user types "env", here it prints and frees cmd tokens, and reprompts user */
	else if (_strcmp(token[0], "env") == 0)
	{
		_env(token, env);
		i = 1;
	}
	/* if user types "cd" , it should change dir */
	else if (_strcmp(token[0], "cd") == 0)
	{
		i = _cd(token, env, num);
	}
	/* if user types "setenv", here it creates or modifies linked list nod */
	else if (_strcmp(token[0], "setenv") == 0)
	{
		_setenv(&env, token);
		i = 1;
	}
	/* if user types "setenv", it removes linked list node */
	else if (_strcmp(token[0], "unsetenv") == 0)
	{
		_unsetenv(&env, token);
		i = 1;
	}
	return (i);
}

/**
 * ignore_space - return string without spaces in front
 * @str: string
 * Return: new string
 */
char *ignore_space(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

/**
 * ctrl_D - exits program if Ctrl-D was entered
 * @i: characters read via get_line
 * @command: user's typed in command
 * @env: envtl variable linked list
 */
void ctrl_D(int i, char *command, list_t *env)
{
	if (i == 0) /* handles Ctrl+D */
	{
		free(command); /* exits with newline if in shell */
		free_linked_list(env);
		if (isatty(STDIN_FILENO))/* ctrl+d prints newline */
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
}

/**
 * prompt - repeatedly prompts user and executes user's cmds if applicable
 * @en: envtl variables
 * Return: 0 on success
 */
int prompt(char **en)
{
	list_t *env;
	size_t i = 0, n = 0;
	int command_line_no = 0, exit_stat = 0;
	char *command, *n_command, **token;

	env = env_linked_list(en);
	do {
		command_line_no++;
		if (isatty(STDIN_FILENO)) /* asks again if in interactive shell */
			write(STDOUT_FILENO, "$ ", 2);
		else
			non_interactive(env);
		signal(SIGINT, ctrl_c); /* ngari: this disables ctrl+c */
		command = NULL; i = 0; /* reset vars each time loop runs */
		i = get_line(&command); /* read user's cmd in stdin */
		ctrl_D(i, command, env); /* exits shell */
		n_command = command;
		command = ignore_space(command);
		n = 0;
		while (command[n] != '\n') /* replaces get_line's \n with \0 */
			n++;
		command[n] = '\0';
		if (command[0] == '\0') /* asks again if user hits enter only */
		{
			free(n_command); continue;
		}
		token = NULL; token = _str_tok(command, " "); /*token user cmd*/
		if (n_command != NULL)
			free(n_command);
		exit_stat = built_in(token, env, command_line_no, NULL);
		if (exit_stat)
			continue;
		exit_stat = _execve(token, env, command_line_no);
	} while (1); 
	/* keeps repeating till user exits shell */
	return (exit_stat);
}
