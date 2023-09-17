#include "shell.h"

/**
 * main - the core function of this shell
 * Return: free and reprint the promt if success
 */

int main()
{
	while (1)
	{
		if (isatty(STDOUT_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}
		getinput();
	}
	return 0;
}