#include"shell.h"

void getinput(void)
{
	char *input = NULL;
	size_t inputsize = 0;
	int inputcount;
	char *tkn;
	char **storage = malloc(sizeof(char *)*MAX_INPUT_SIZE);
	pid_t process;
	int state, i = 0, j = 0;


	while (1)
	{
		prompt();
		inputcount = getline(&input, &inputsize, stdin);

		if (inputcount == -1) {
            printf("\n"); /*EOF*/
            break;
        }

		tkn = strtok(input, " \t\n");

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
			if (execve(storage[0], storage, NULL) == -1)
				perror("execve");
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