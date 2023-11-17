#include "shell.h"

/**
 * _env - prints the environ
 *
 * Return: 0 on success
 */
int _env(void)
{

    int count;

    for (count = 0; environ[count]; count++)
	    _puts(environ[count]); /*arr of envi */
    return (0);
}
/**
 * _getenv - gets path member from environ
 * @name: pointer to Path string
 *
 * Return: pointer to path member string or NULL if not found
 */
char *_getenv(const char *name)
{
    /* retrieve value of a specific environment variable given its name*/
    int i, res;

    for (i = 0; environ[i]; i++)
    {
	    res = is_path_var(name, environ[i]);
	    if (res == 0)
	    {
		    return (environ[i]);
	    }
    }
    return (NULL);
}

/**
 * is_path_var - compares path with environ to find PATH value
 * @s1: pointer PATH string
 * @s2: pointer to environ string with actual value
 *
 * Return: 0 on success
 */
int is_path_var(const char *s1, const char *s2)
{
    int i;

    for (i = 0; s2[i] != '='; i++)
    {
	    if (s1[i] != s2[i])
		    return (0);/*not equal*/
    }
    return (1); /*equal */
}
