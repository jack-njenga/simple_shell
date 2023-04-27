#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <ctype.h>

/*structures*/

/*global variable*/
extern char **environ;


int check_keyword(char *args[], char *buffer);
void _fork(char *full_path, char *args[], char *env[], int *st);
int argument(char *buffer, char *dell, char *envp[]);
char *check_path(char *command);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void _free(char *fpath, char *ar, char *arg);
void free_exit(char *buffer, int status);
char *tokenize(char *buffer, char *delim);
void prompt(int fd, struct stat bf);
void _puts(char *str);
void process_buffer(char *buffer, char *argv0, int *status);

#endif
