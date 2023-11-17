#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: character array to fill
 * @b: constant byte to fill with
 * @n: how many bytes to fill
 * Return: the pointer to the char array
 */
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
	    s[i] = b;
    return (s);
}
/**
 * _puts - prints a string
 * @str: string to print
 */
void _puts(char *str)
{
    int co;

    for (co = 0; str[co] != '\0'; co++)
	    _putchar(str[co]);
    _putchar('\n');
}
/**
 * _putchar - prints a character to stdout
 * @c: character to print
 *
 * Return: return value of write syscall
 */
int _putchar(char c)
{
    return (write(1, &c, 1));
}
/**
 * _strcmp -function to compares two strings
 * @s1: first string to compare
 * @s2: second string to compare
 *
 * Return: less than 0 if s1 is less than s2, 0 if they're equal,
 * more than 0 if s1 is greater than s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0' && *s2 == '\0')
		{
			return (0);/*both are equal*/
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2); /*indicates the different*/
}

/**
 * _concat - concats user string with PATH member string and /
 * @tmp: static array to store concatenated string
 * @av: pointer to array of user strings
 * @toke: pointer to PATH token
 *
 * Return: 0 on success
 */
char *_concat(char *tmp, char **av, char *toke)
{
    int leng = 0;

    _memset(tmp, 0, sizeof(tmp));
    leng = _strlen(toke) + _strlen(av[0]) + 2;
    _strcat(tmp, toke);
    _strcat(tmp, "/");
    _strcat(tmp, av[0]);
    tmp[leng - 1] = '\0';
    return (tmp);
}
