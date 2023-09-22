#include "shell.h"


char **splitter2(char *buf) {
	char **tokens = NULL;
	char *token = NULL;
	int i = 0;

	tokens = malloc(sizeof(char *) * 1024);
	if (tokens == NULL) {
		perror("Error");
		return (NULL);
	}
	token = strtok(buf, " \t\n");
	while (token != NULL) {
		tokens[i] = token;
		token = strtok(NULL, " \t\n");
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
