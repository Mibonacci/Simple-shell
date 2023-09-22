#include "shell.h"


char *_getenv(char *key) {
	unsigned int i = 0;
	char *path;
	char **env;
	int count = 0, j = 0;

	while (environ[count])
		count++;

	env = malloc(sizeof(char *) * (count + 1));

	for (j = 0; j < count; j++)
		env[j] = mystrdup(environ[j]);

	env[count] = NULL;

	while (env[i]) {
		path = strtok(env[i], "=");
		if (mystrcmp(key, env[i]) == 0) {
			path = strtok(NULL, "\n");
			return (path);
		}
		i++;
	}
	return (NULL);
}


int envlength(char **env) {
	int i = 0;

	while (env[i])
		i++;
	return (i);
}
