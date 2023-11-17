#include "shell.h"
/**
 * prompt - writes or display a prompt
 *
 * Return: 0 (Success) -1 on Fail
 */
int prompt(void)
{
    /*char *prompt = "$ ";*/
    ssize_t line = 0;

    if (isatty(STDIN_FILENO) == 1)
    {
	    line = write(STDOUT_FILENO, "$ ", 2);
	    if (line == -1) /*on exit or Cl+d */
		    return (-1); /*exit(0) */
    }
    return (0);
}
/**
 * checkbuiltin - check if first user string is a built-in
 * @av: pointer to array of user of strings
 * @buffer: pointer to user string
 * @exit_st: exit status of execve
 * Return: 1 if user string is equal to env or 0 otherwise
 */
int checkbuiltin(char **av, char *buffer, int exit_st)
{
    int f1;

    if (_strcmp(av[0], "env") == 0)
    {
        _env();
        for (f1 = 0; av[f1]; f1++)
            free(av[f1]);
        free(av);
        free(buffer);
        return (1);
    }
    else if (_strcmp(av[0], "exit") == 0)
    {
        for (f1 = 0; av[f1]; f1++)
            free(av[f1]);
        free(av);
        free(buffer);
        exit(exit_st);
    }
    else
        return (0);
}
