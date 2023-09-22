#include "shell.h"


void freearray(char **array) {
	int i = 0;

	while (array[i] != NULL) {
		free(array[i]);
		i++;
	}
	free(array);
}
