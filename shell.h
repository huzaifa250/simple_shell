#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

extern char **environ;

/*program flow */

int prompt(void);
char *_read(void);
char *_pathbuffer(char **av, char *PATH, char *copy);
int fork_process(char **av, char *buffer, char *Fullpathbuffer);
int checkbuiltin(char **av, char *buffer, int exit_st);

/*Tokenize & helper functions */
char **tokenizer(char *buffer);
char *_strdup(char *str);
int split_string(char *str);
int _split_path(char *str);
char *_concat(char *tmp, char **av, char *toke);
int is_path_var(const char *s1, const char *s2);

/*help function */
int _putchar(char c);
void _puts(char *str);
int _strlen(char *s);
char *_strcat(char *dest, char *sr);
char *_memset(char *s, char b, unsigned int n);
int _strcmp(char *s1, char *s2);
int _env(void);
char *_getenv(const char *name);

#endif

