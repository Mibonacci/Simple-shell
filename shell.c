#include "shell.h"

/**
 * all the functions are in one file you know why
*/

char *my_getline(void) {
    char *line = NULL;
    char *newline;
    size_t line_size = 0;
    ssize_t read_bytes;

    while (1) {
        if (buffer_position >= buffer_size) {
            read_bytes = read(STDIN_FILENO, input_buffer, sizeof(input_buffer));

            if (read_bytes == -1) {
                perror("my_getline");
                exit(EXIT_FAILURE);
            } else if (read_bytes == 0) {
                if (line_size == 0) {
                    free(line);
                    return NULL;
                } else {
                    buffer_position = 0;
                    buffer_size = 0;
                    break;
                }
            } else {
                buffer_position = 0;
                buffer_size = read_bytes;
            }
        }

        newline = memchr(input_buffer + buffer_position, '\n', buffer_size - buffer_position);
        if (newline != NULL) {
            size_t line_length = newline - (input_buffer + buffer_position);
            line = realloc(line, line_size + line_length + 1);

            if (line == NULL) {
                perror("my_getline");
                exit(EXIT_FAILURE);
            }

            memcpy(line + line_size, input_buffer + buffer_position, line_length);
            line_size += line_length;
            line[line_size] = '\0';

            buffer_position += line_length + 1;
            break;
        } else {
            line = realloc(line, line_size + buffer_size - buffer_position + 1);

            if (line == NULL) {
                perror("my_getline");
                exit(EXIT_FAILURE);
            }

            memcpy(line + line_size, input_buffer + buffer_position, buffer_size - buffer_position);
            line_size += buffer_size - buffer_position;
            buffer_position = buffer_size;
        }
    }

    return line;
}

void collapse_spaces(char *line) {
    char *dest = line;
    char prev_char = ' ';

    while (*line) {
        if (*line == ' ' && prev_char == ' ') {
            line++;
        } else {
            *dest++ = *line++;
            prev_char = *(dest - 1);
        }
    }
    *dest = '\0';
}

char **split_line(char *line) {
    int bufsize = MAX_INPUT_SIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        perror("split_line");
        exit(EXIT_FAILURE);
    }

    line[strcspn(line, "\n")] = '\0';

    token = strtok(line, " \t\r\n\a");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += MAX_INPUT_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                perror("split_line");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

void write_output(const char *str) {
    size_t len = strlen(str);
    write(STDOUT_FILENO, str, len);
}

int execute_command(char **args) {
    pid_t pid;
    int status;
    char *path = getenv("PATH");
    char *token;
    
    if (path == NULL) {
        perror("execute_command");
        exit(EXIT_FAILURE);
    }

    token = strtok(path, ":");
    
    while (token != NULL) {
        size_t full_path_len = strlen(token) + strlen(args[0]) + 2;/*2 for NULL*/
        char *full_path = (char *)malloc(full_path_len);
        
        if (full_path == NULL) {
            perror("execute_command");
            exit(EXIT_FAILURE);
        }

        snprintf(full_path, full_path_len, "%s/%s", token, args[0]);

        if (access(full_path, X_OK) == 0) {
            pid = fork();
            if (pid == 0) {
                if (execve(full_path, args, NULL) == -1) {
                    perror("execute_command");
                    exit(EXIT_FAILURE);
                }
            } else if (pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else {
                do {
                    waitpid(pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
                free(full_path);
                return 1;
            }
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    fprintf(stderr, "Command not found: %s\n", args[0]);
    return 1;
}

int execute_shell_command(char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }

    /* Execute command */
    return execute_command(args);
}

void shell_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        write_output("$ ");
        line = my_getline();

        if (line == NULL) {
            break;
        }
        args = split_line(line);
        status = execute_shell_command(args);

        free(line);
        free(args);
    } while (status);
}

int main(void) {
    shell_loop();
    return EXIT_SUCCESS;
}