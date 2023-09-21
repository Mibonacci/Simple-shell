#include "shell.h"

/**
 * all the functions are in one file you know why
*/

int execute_command(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        char *env[] = { NULL };
        if (execve(args[0], args, env) == -1) {
            perror("");
        }
        exit(EXIT_FAILURE);

    } else if (pid < 0) {
        perror("");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int execute_shell_command(char **args)
{
    if (args[0] == NULL) {
        return 1;
    }
    /*execute command*/
    return execute_command(args);
}

char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            perror("");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

char **split_line(char *line)
{
    int bufsize = MAX_INPUT_SIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        perror("");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\a");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += MAX_INPUT_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                perror("");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

void write_output(const char *str)
{
    size_t len = strlen(str);
    write(STDOUT_FILENO, str, len);
}

void shell_loop(void)
{
    char *line;
    char **args;
    int status;

    do {
        write_output("$ ");
        line = read_line();
        args = split_line(line);
        status = execute_shell_command(args);

        free(line);
        free(args);
    } while (status);
}

int main(void)
{
    shell_loop();
    return EXIT_SUCCESS;
}