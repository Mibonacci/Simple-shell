#include"shell.h"

char *my_getline(void) {
    char *line = NULL;
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
                }
                break;
            } else {
                buffer_position = 0;
                buffer_size = read_bytes;
            }
        }

        char *newline = memchr(input_buffer + buffer_position, '\n', buffer_size - buffer_position);
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

int main(void) {
    char *line;

    while (1) {
        line = my_getline();
        if (line == NULL) {
            write(STDOUT_FILENO, "EOF reached. Exiting.\n", 21);
            break;
        }

        write(STDOUT_FILENO, "You entered: ", 13); 
        write(STDOUT_FILENO, line, strlen(line));
        write(STDOUT_FILENO, "\n", 1);

        free(line);
    }

    return 0;
}