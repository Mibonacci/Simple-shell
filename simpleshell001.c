#include"shell.h"

int inputcount;

void prompt(void)
{
        write(STDOUT_FILENO, "$ ", 2);
}

void getinput(void)
{
	char *input = NULL;
	size_t inputsize = 0;
	char *tkn;
	char **storage = malloc(sizeof(char *)*MAX_INPUT_SIZE);
	pid_t process;
	int state, i = 0, j = 0;


	while (1)
	{
		inputcount = getline(&input, &inputsize, stdin);
		prompt();
		if (getline(&input, &inputsize, stdin) == -1) {
            printf("\n");
            break;
		}

		tkn = strtok(input, " \t\n");
		i = 0;

		while(tkn)
		{
			storage[i] = strdup(tkn);
			tkn = strtok(NULL, " \t\n");
			i++;
		}
		storage[i] = NULL; /*terminate arg list*/

		process = fork();

		if (process == 0)
		{
			if (execve(storage[0], storage, NULL) == -1){
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		if (process == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&state);
		}
		while (storage[j] != NULL)
			{
    			free(storage[j]);
    			j++;
			}
		i = 0;
	}
}