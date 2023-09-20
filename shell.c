#include "shell.h"

/**
 * exec - regular execute function
*/

int exec(char **args) {
    pid_t process;
    int status;

    if (args[0] == NULL) {
        return 1;
    }

    process = fork();
    if (process == 0) {
        if (execve(args[0], args, NULL) == -1) {
            perror("");
            exit(EXIT_FAILURE);
        }
    } else if (process < 0) {
        perror("fork");
    } else {
        do {
            waitpid(process, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

void prompt(void)
{
    char input[MAX_INPUT_SIZE];
    char output[MAX_INPUT_SIZE];
    char *args[MAX_INPUT_SIZE];
    char *spacing = input;
    char *outputPtr = output;
	char *inputclone;
	char promptStr[] = "$ ";
	char *token;
    int i;

    while (1)
    {
        write(STDOUT_FILENO, promptStr, sizeof(promptStr) - 1);
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            perror("");
            exit(EXIT_FAILURE);
        }

		input[strcspn(input, "\n")] = '\0';

        /*this is to override multiple spaces between command arguments*/
        while (*spacing)
        {
            *outputPtr++ = *spacing++;
            while (isspace(*spacing) && (outputPtr == output || !isspace(outputPtr[-1])))
            {
                spacing++;
            }
        }
        *outputPtr = '\0';

        inputclone = strdup(output);
        if (inputclone == NULL)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }

        i = 0;
        token = strtok(output, " \t\n");
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[i] = NULL;
        exec(args);

		free(inputclone);
    }
}

int main()
{
    prompt();
    return 0;
}