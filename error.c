#include "shell.h"


void printerror2(char *argv, int count, char *cmd, char *msg) {
	char *count_str = NULL;

	write(STDERR_FILENO, argv, constcharlength(argv));
	write(STDERR_FILENO, ": ", 2);
	count_str = itoa(count);
	write(STDERR_FILENO, count_str, constcharlength(count_str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, msg, constcharlength(msg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, constcharlength(cmd));
	write(STDERR_FILENO, "\n", 1);
	free(count_str);
}