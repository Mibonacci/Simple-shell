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
        perror("");
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
    char *token;
    int i;

    while (1) {
        write(STDOUT_FILENO, "$ ", 2);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("");
            exit(EXIT_FAILURE);
        }

        input[strcspn(input, "\n")] = '\0';

        i = 0;
        token = strtok(input, " \t\n");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[i] = NULL;
        
        if (i > 0) {
            if (strcmp(args[0], "exit") == 0) {
                exit(0);
            }
        }

        exec(args);
    }
}

int main() {
    prompt();
    return 0;
}