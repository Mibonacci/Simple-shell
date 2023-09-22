#include "shell.h"

/**
 * The main file of shell
 */

int main(int ac, char **av, char **env) {
	char *buf = NULL;
	size_t buf_size = 0;
	int n_characters = 0;
	int shell = 1;
	(void)ac;

	signal(SIGINT, sigintfunc);
	while (shell) {
		if (isatty(STDIN_FILENO)) {
			fflush(stdin);
			write(STDOUT_FILENO, "$ ", 2);
		}
		n_characters = mygetline(&buf, &buf_size, STDIN_FILENO);
		splitstr(buf);
		if (n_characters == EOF) {
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (n_characters > 1)
			buf[n_characters - 1] = '\0';
		if (buf[0] == '\n')
			continue;
		inputhandler(buf, env, av);
		buf_size = 0;
		buf = NULL;
	}
	free(buf);
	return (0);
}

void sigintfunc(int signal) {
	(void)signal;
	write(STDOUT_FILENO, "\n$ ", 3);
}




