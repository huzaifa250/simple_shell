#include "shell.h"
/**
 * _read - reads stdin and stores it in a buffer
 *
 * Return: a pointer to the buffer
 */
char *_read(void)
{
    ssize_t read_buf = 0;
    size_t n = 0;
    char *buffer = NULL;
   /* int i = 0;*/

    read_buf = getline(&buffer, &n, stdin);
    if (isatty(STDIN_FILENO) != 0)
	    write(STDOUT_FILENO, "\n", 1);
    if (read_buf == -1) /*fail */
    {
	    free(buffer);
	    exit(0); /*return -1 */
    }
    return (buffer);
}

/**
 * _pathbuffer - finds the string to call execve on
 * @av: pointer to array of user of strings
 * @PATH: pointer to PATH string
 * @copy: pointer to copy of PATH string
 *
 * Return: a pointer to string to call execve on
 */
char *_pathbuffer(char **av, char *PATH, char *copy)
{
    char *toke, *Fullpathbuffer = NULL, *concatstr = NULL;
    static char tmp[256];
    int path_count = 0, fullpathflag = 0, w = 0, toklen = 0;
    struct stat h;

    copy = NULL;
    copy = _strdup(PATH);
    path_count = _split_path(copy);
    toke = strtok(copy, ": =");
    while (toke != NULL)
    {
	    concatstr = _concat(tmp, av, toke);
	    if (stat(concatstr, &h) == 0)
	    {
		    Fullpathbuffer = concatstr;
		    fullpathflag = 1;
		    break;
	    }
	    if (w < path_count - 2)
	    {
		    toklen = _strlen(toke);
		    if (toke[toklen + 1] == ':')
		    {
			    if (stat(av[0], &h) == 0)
			    {
				    Fullpathbuffer = av[0];
				    fullpathflag = 1;
				    break;
			    }
		    }
	    }
	    w++;
	    toke = strtok(NULL, ":");
    }
    if (fullpathflag == 0)
	    Fullpathbuffer = av[0];
    free(copy);
    return (Fullpathbuffer);
}
/**
 * fork_process - create child process to execute based on user input
 * @av: pointer to array of user of strings
 * @buffer: pointer to user string
 * @Fullpathbuffer: pointer to user input
 *
 * Return: 0 on (success)
 */
int fork_process(char **av, char *buffer, char *Fullpathbuffer)
{
    int i, status, res, exit_status = 0;
    pid_t c_pid;

    c_pid = fork();
    if (c_pid == -1)
    {
	    perror("Error");
	    exit(1);
    }
    if (c_pid == 0)
    {
	    res = execve(Fullpathbuffer, av, NULL);
	    if (res == -1)
	    {
		    perror(av[0]);
		    for (i = 0; av[i]; i++)
			    free(av[i]);
		    free(av);
		    free(buffer);
		    exit(127);
	    }
    }
    wait(&status); /*wait chaild */
    if (WIFEXITED(status))
    {
	    exit_status = WEXITSTATUS(status);
    }
    for (i = 0; av[i]; i++)
	    free(av[i]);
    free(av);
    free(buffer);
    return (exit_status);
}

