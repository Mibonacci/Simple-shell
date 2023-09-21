#ifndef MAIN_H
#define MAIN_H
#define MAX_ARGS 4096
#define MAX_INPUT_SIZE 4096
#define READ_SIZE 4096
#define TOK_D " \t\r\n\a\""
#define INITIAL_bf_SIZE 64
#define GROW_FACTOR 2

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

/*prototypes*/
int exec(char **args);
void prompt(void);
char *my_getline(void);

/*special to getline*/
#define MAX_BUFFER_SIZE 256

static char input_buffer[MAX_BUFFER_SIZE];
static int buffer_position = 0;
static int buffer_size = 0;


#endif

