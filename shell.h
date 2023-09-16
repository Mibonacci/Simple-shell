#ifndef MAIN_H
#define MAIN_H
#define MAX_ARGS 4096
#define READ_SIZE 4096
#define TOK_D " \t\r\n\a\""
#define INITIAL_bf_SIZE 64
#define GROW_FACTOR 2

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void getinput();


#endif

