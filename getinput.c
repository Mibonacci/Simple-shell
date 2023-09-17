#include"shell.h"

void getinput(void)
{
	char *input = NULL;
	size_t input_length = 0;
	pid_t child_pid, wait_pid;
	int status;

	while(1)
	{
		/*read input from stream*/
		ssize_t bytes_read = getline(&input, &input_length, stdin);

		if (bytes_read == -1)
		{
		/*handling EOF or ctrlD*/
			break;
		}

		/*handling special character new line*/
		if (bytes_read > 0 && input[bytes_read - 1] == '\n')
		{
			input[bytes_read - 1] = '\0';
		}

		/*Fork*/
		child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (child_pid == 0)
		{
			/*if execlp returns error child process terminates*/
			execlp(input, input, NULL);
			perror(input);
			exit(EXIT_FAILURE);
		}
		else
		{
			/*pprocess waits for the child*/
			wait_pid = wait(&status);
			if (wait_pid == -1)
			{
				perror("wait");
				exit(EXIT_FAILURE);
			}
		}
	}
	free(input);
}