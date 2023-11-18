#include "shell.h"

/**
 * _line - assigns the line var for get_line
 * @linepoint: Buffer that store the input str
 * @buffer: str that is been called to line
 * @sn: size of line
 * @j: size of buffer
 */
void _line(char **linepoint, size_t *sn, char *buffer, size_t j)
{

	if (*linepoint == NULL)
	{
		if  (j > BUFSIZE)
			*sn = j;

		else
			*sn = BUFSIZE;
		*linepoint = buffer;
	}
	else if (*sn < j)
	{
		if (j > BUFSIZE)
			*sn = j;
		else
			*sn = BUFSIZE;
		*linepoint = buffer;
	}
	else
	{
		_strcpy(*linepoint, buffer);
		free(buffer);
	}
}
/**
 * get_line - Read inpt from stream
 * @linept: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **linept, size_t *n, FILE *stream)
{
	int i;
	static ssize_t inp;
	ssize_t ret;
	char *buffer;
	char t = 'z';

	if (inp == 0)
		fflush(stream);
	else
		return (-1);
	inp = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && inp == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && inp != 0)
		{
			inp++;
			break;
		}
		if (inp >= BUFSIZE)
			buffer = _realloc(buffer, inp, inp + 1);
		buffer[inp] = t;
		inp++;
	}
	buffer[inp] = '\0';
	_line(linept, n, buffer, inp);
	ret = inp;
	if (i != 0)
		inp = 0;
	return (ret);
}
