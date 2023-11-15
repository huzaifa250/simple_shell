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


#define BUFSIZE 1024
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define TOK_DELIM " \n\r\t\a"
#define BUF_FLUSH -1

#define USE_GETLINE
#define USE_STRTOK

#define CMD_NORM

#define CMD_CHAIN

#define INFO_INIT \
{ \
    NULL,   /* arg */ \
    NULL,   /* argv */ \
    NULL,   /* path */ \
    0,      /* argc */ \
    0,      /* readfd */ \
    NULL,   /* cmd_buf */ \
    NULL,   /* env */ \
    NULL,   /* environ */ \
    0,      /* mode */ \
    0,      /* flags */ \
}

extern char **environ;


/**
 *struct pasarinfo - contains arguements pass into a function,
 *              allowing prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings that generated from arg
 *@path: a string path for the current command
 *@argc: the count number of argument
 *@line_count: count error
 *@err_num: error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: modified copy of environ from LL env
 *@env_changed: if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 */
typedef struct pasarinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	lst_t *env;
	char **environ;
	int env_changed;
	int status;
	char env;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
} info_st;
/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_st *);
} builtin_table;

/**
 * struct liststr - singly linked list
 * @num: number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} lst_t;

/* shelloop.c */
int hsh(info_st *, char **);
int f_builtin(info_st *);
void f_cmd(info_st *);
void fork_cmd(info_st *);

/* parser.c */
int is_cmd(info_st *, char *);
char *dup_chars(char *, int, int);
char *f_path(info_st *, char *, char *);

/* loophash.c and strings */
int loophash(char **);
void _puts(char *);
int _putchar(char);
int _strlen(char *);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

int _getline(info_st *, char **, size_t *);
int prompt(info_st *);
int is_delim(char, char *);
char *starts_with(const char *, const char *);

int special_exit(info_st *info);
int sp_cd(info_st *info);
int my_help(info_st *info);
int my_env(info_st *info);
int populate_env_list(info_t *);
void dell_info(info_st *);
void info_set(info_st *, char **);
void info_free(info_st *, int);

int is_chain(info_st *, char *, size_t *);
void check_chain(info_st *, char *, size_t *, size_t, size_t);


/*input */
ssize_t get_input(info_st *);
int _getline(info_st *, char **, size_t *);
void sigint_handler(int);

/* memory*/
void ffree(char **);

/* error */
void print_error(info_st *, char *);
void remove_comments(char *);

#endif /*SHELL_H_INCLUDED*/
