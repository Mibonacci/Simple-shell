#include "shell.h"


char *createpath(char *path, char *cmd) {
	char *cmd_path = NULL;

	cmd_path = malloc(sizeof(char) * (mystrlen(path) + mystrlen(cmd) + 2));
	if (cmd_path == NULL)
		return (NULL);
	mystrcpy(cmd_path, path);
	_strcat(cmd_path, "/");
	_strcat(cmd_path, cmd);
	return (cmd_path);
}


char *getpath(char *cmd) {
	char *path = NULL, *path_copy = NULL, *token = NULL, *cmd_path = NULL;
	struct stat st;

	if (stat(cmd, &st) == 0)
		return (cmd);
	if (cmd == NULL)
		return (NULL);
	if (cmd[0] == '/') {
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	path = _getenv("PATH");
	path_copy = mystrdup(path);
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		cmd_path = createpath(token, cmd);
		if (stat(cmd_path, &st) == 0) {
			free(path_copy);
			return (cmd_path);
		}
		free(cmd_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
