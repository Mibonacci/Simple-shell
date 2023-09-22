#include "shell.h"

void printenv(char **env) {
	int i = 0;

	while (env[i] != NULL) {
		write(STDOUT_FILENO, env[i], mystrlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}


int builtins(char **tokens, char **env) {
	if (builtins1(tokens, env))
		return (1);
	if (builtins2(tokens))
		return (1);
	if (builtins3(tokens))
		return (1);
	return (0);
}


int builtins1(char **tokens, char **env) {
	int i = 0;

	if (mycuststrncmp(tokens[0], "exit", 4) == 0)
		exit(EXIT_SUCCESS);
	if (mycuststrncmp(tokens[0], "env", 3) == 0)
	{
		while (env[i] != NULL)
		{
			write(STDOUT_FILENO, env[i], mystrlen(env[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
		return (1);
	}
	return (0);
}


int builtins2(char **tokens) {
	if (mycuststrncmp(tokens[0], "setenv", 6) == 0) {
		if (tokens[1] == NULL) {
			write(STDERR_FILENO, "Usage: setenv [VARIABLE] [VALUE]\n", 33);
			return (1);
		}
		if (tokens[2] == NULL) {
			return (1);
		}
		return (1);
	}
	if (mycuststrncmp(tokens[0], "unsetenv", 8) == 0) {
		if (tokens[1] == NULL) {
			write(STDERR_FILENO, "Usage: unsetenv [VARIABLE]\n", 27);
			return (1);
		}
		return (1);
	}
	return (0);
}

int builtins3(char **tokens) {
	if (mycuststrncmp(tokens[0], "clear", 5) == 0) {
		write(STDOUT_FILENO, "\033[H\033[J", 6);
		return (1);
	}
	if (mycuststrncmp(tokens[0], "echo", 4) == 0) {
		myecho(tokens, NULL);
		return (1);
	}
	if (mycuststrncmp(tokens[0], "cd", 2) == 0) {
		mycd(tokens);
		return (1);
	}
	return (0);
}
