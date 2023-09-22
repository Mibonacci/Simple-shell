#include "shell.h"


char **splitter1(char *str, char *delim) {
	char **tokens = NULL;
	char *token = NULL;
	int i = 0, bufsize = 0;

	if (str == NULL)
		return (NULL);
	bufsize = mystrlen(str);
	tokens = malloc(sizeof(char *) * bufsize);
	if (tokens == NULL)
		return (NULL);
	token = strtok(str, delim);
	while (token != NULL) {
		tokens[i] = token;
		token = strtok(NULL, delim);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}


int inputhandler(char *buf, char **env, char **av) {
	char **tokens = NULL, **cmd = NULL;
	int i = 0, bufsize = 0;

	bufsize = mystrlen(buf);
	cmd = malloc(sizeof(char *) * bufsize);
	if (cmd == NULL)
		return (-1);
	tokens = splitter1(buf, ";\n");
	while (tokens[i] != NULL)
	{
		cmd = splitter1(tokens[i], " \t\r\n\a");
		if (cmd[0] != NULL)
			execcomd(cmd, env, av);
		free(cmd);
		i++;
	}
	free(tokens);
	return (0);
}
