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
char _read(void);
char *_pathbuffer(char **av, char *PATH, char *copy);
int fork_process(char **av, char *buffer, char *Fullpathbuffer);

/*Tokenize & helper functions */
char **tokenizer(char *buffer);
char *_strdup(char *str);
int split_string(char *str);

/*help function */
void _putchar(char c);
void _puts(char *str);

#endif

