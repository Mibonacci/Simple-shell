#ifndef MAIN_H
#define MAIN_H
#define MAX_ARGS 1024
#define MAX_INPUT_SIZE 1024
#define READ_SIZE 1024
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

/*prototypes*/
int exec(char **args);


#endif

