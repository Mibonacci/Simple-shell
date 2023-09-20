#include "shell.h"

/**
 * exec - execute function
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
            perror("execve");
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

void prompt(void) {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_INPUT_SIZE];
	char promptStr[] = "$ ";
	char *token;
    int i;

    while (1) {
        write(STDOUT_FILENO, promptStr, sizeof(promptStr) - 1);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("");
            exit(EXIT_FAILURE);
        }

        i = 0;
        token = strtok(input, " \t\n");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[i] = NULL;
        exec(args);
    }
}

int main()
{
    prompt();
    return 0;
}