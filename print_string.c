#include "shell.h"


/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: 1 on (success).
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_eputs - prints an input string
 * @str: string to be printed
 *
 * Return: void
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}


/**
 * _putfd - writes the character c to given filedescriptor
 * @c: Is character to print
 * @fd: The filedescriptor to write to
 *
 * Return: 1 (success).
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
/**
 * starts_with - checks if prefix starts with hstr
 * @hstr: string to search
 * @prefix: the substring to find
 *
 * Return: address of next char of hstr or NULL
 */
char *starts_with(const char *hstr, const char *prefix)
{
	while (*prefix != '\0')
		if (*prefix++ != *hstr++)
			return (NULL);
	return ((char *)hstr);
}
