#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdbool.h>

extern char **environ;

int check_keyword(char *args[]);
void _fork(char *full_path, char *args[], char *env[], int *st);
int argument(char *buffer, char *dell, char *envp[]);
char *check_path(char *command);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void _free(char *fpath, char *args);
void free_exit(char *buffer);
char *tokenize(char *buffer, char * delim);

#endif
