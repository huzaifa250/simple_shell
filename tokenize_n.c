#include "shell.h"
/**
 * tokenizer - creates array of tokens based on user string
 * @buffer: pointer to user string
 *
 * Return: pointer to array of user strings
 */
char **tokenizer(char *buffer)
{
    char *token;
    int i = 0, word_count = 0;
    char *delimiter = " \n";
    char **av;

    word_count = split_string(buffer);
    if (!word_count)
	    return (NULL);
    av = malloc((word_count + 1) * sizeof(char *));
    if (av == NULL)
	    exit(1);
    token = strtok(buffer, delimiter);
    while (token != NULL)
    {
	    av[i] = _strdup(token);
	    token = strtok(NULL, delimiter);
	    i++;
    }
    av[i] = NULL;
    return (av);
}
/**
 * _split_path - counts the number of PATH members
 * @str: pointer to string to count
 *
 * Return: number of PATH members
 */
int _split_path(char *str)
{
    int i;
    int searchflag = 1;
    int word_count = 0;

    for (i = 0; str[i]; i++)
    {
	    if (str[i] != ':' && searchflag == 1)
	    {
		    word_count += 1;
		    searchflag = 0;
	    }
	    if (str[i + 1] == ':')
	    {
		    searchflag = 1;
	    }
    }
    return (word_count);
}
