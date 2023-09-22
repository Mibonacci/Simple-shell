#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define READ_SIZE 4096
#define BUFSIZE 4096

/*global variables*/

extern char **environ;

/*prototypes*/

ssize_t mygetline(char **buffer, size_t *bufsize, int fd);
int inputhandler(char *buf, char **env, char **av);
void sigintfunc(int sigint);
char **splitter1(char *str, char *delim);
int builtins(char **tokens, char **env);
int builtins1(char **tokens, char **env);
int builtins2(char **tokens);
int builtins3(char **tokens);
int mystrlen(char *str);
char **splitter2(char *buf);
void printenv(char **env);
int mystrcmp(char *s1, char *s2);
int mycuststrncmp(char *str1, char *str2, int n);
char *mystrdup(char *str);
char *concatpaths(char *dest, char *src);
char *itoa(int num);
char *mystrcpy(char *dest, char *src);
int constcharlength(const char *str);
int runbaby(char **tokens, char **env);
int envlength(char **env);
void printerror2(char *av, int count, char *cmd, char *msg);
char *_strchr(char *s, char c);
char *_strtok(char *str, char *delim);
char *_strcat(char *dest, char *src);
char *getpath(char *cmd);
char *createpath(char *path, char *cmd);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getenv(char *key);
void freearray(char **array);
void myechoargs(char *tokens, int *status);
char *env2(char *key);
char *splitstr(char *str);
int comdchecker(char *cmd);
int execcomd(char **tokens, char **env, char **av);
void printerror(char **tokens, char **av);
void mycd(char **args);
void change_directory(char **directories, char *command_name);
int myecho(char **tokens, int *status);

#endif

/*custom functions*/
