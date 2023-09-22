#include "shell.h"


void printerror(char **tokens, char **av)
{
	write(STDERR_FILENO, av[0], mystrlen(av[0]));
	write(STDERR_FILENO, ": line 1: ", 10);
	write(STDERR_FILENO, tokens[0], mystrlen(tokens[0]));
	write(STDERR_FILENO, ": command not found\n", 20);
}


int runbaby(char **tokens, char **env)
{
	pid_t pid;
	int status;
	char *path;
	struct stat st;

	if (stat(tokens[0], &st) == 0)
		path = mystrdup(tokens[0]);
	else
		path = getpath(tokens[0]);
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		free(path);
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(path, tokens, env) == -1)
		{
			perror("Error");
			free(path);
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}
	free(path);
	return (0);
}


int execcomd(char **tokens, char **env, char **av)
{
	int is_built_in = 0, cmd_exits = 0;

	is_built_in = builtins(tokens, env);
	cmd_exits = comdchecker(tokens[0]);
	if (is_built_in == 0 && cmd_exits == 1)
	{
		runbaby(tokens, env);
		return (0);
	}
	if (is_built_in == 0 && cmd_exits == 0)
	{
		printerror(tokens, av);
		return (1);
	}
	return (0);
}
