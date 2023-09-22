#include "shell.h"


char *env2(char *key) {
	char *value = NULL;
	int i = 0, j = 0, len_key = 0;

	if (key == NULL)
		return (NULL);
	len_key = mystrlen(key);
	while (environ[i])
	{
		while (environ[i][j] == key[j])
		{
			if (j == len_key - 1)
			{
				value = environ[i] + len_key + 1;
				return (value);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (NULL);
}


void myechoargs(char *tokens, int *status)
{
	char *value = NULL;
	(void)status;

	if (tokens == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return;
	}
	if (mycuststrncmp(tokens, "$", 1) == 0)
	{
		value = env2(tokens + 1);
		if (value != NULL)
		{
			write(STDOUT_FILENO, value, mystrlen(value));
			write(STDOUT_FILENO, "\n", 1);
			return;
		}
	}
	if (mycuststrncmp(tokens, "$$", 2) == 0)
	{
		value = itoa(getpid());
		write(STDOUT_FILENO, value, mystrlen(value));
		write(STDOUT_FILENO, "\n", 1);
		free(value);
		return;
	}
	if (mycuststrncmp(tokens, "$?", 2) == 0)
	{
		write(STDOUT_FILENO, env2("?"), mystrlen(env2("?")));
		write(STDOUT_FILENO, "\n", 1);
		free(value);
		return;
	}
	write(STDOUT_FILENO, "\n", 1);
}


int myecho(char **tokens, int *status)
{
	int i = 1, flag = 0, j = 0;

	if (tokens == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	if (mycuststrncmp(tokens[0], "echo", 4) != 0)
		return (0);
	if (tokens[1] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	if (mycuststrncmp(tokens[1], "$", 1) == 0 || mycuststrncmp(tokens[1], "$$", 2) == 0 ||
	    mycuststrncmp(tokens[1], "$?", 2) == 0)
	{
		myechoargs(tokens[1], status);
		return (1);
	}
	for (i = 1; tokens[i] != NULL; i++)
	{
		for (j = 0; tokens[i][j] != '\0'; j++)
		{
			if (tokens[i][j] == '$')
			{
				flag = 1;
				myechoargs(tokens[i] + j, status);
				break;
			}
			if (tokens[i][j] != '"')
				write(STDOUT_FILENO, &tokens[i][j], 1);
		}
		if (tokens[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (1);
}
