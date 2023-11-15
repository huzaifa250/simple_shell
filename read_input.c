#include "shell.h"

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: pointer address to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: sl (length of string)
 */
int _getline(info_st *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, leng;
	size_t j;
	ssize_t k = 0, sl = 0;
	char *p = NULL, *new_pro = NULL, *c;

	p = *ptr;
	if (p && length)
		sl = *length;
	if (i == leng)
		i = leng = 0;
	k = read_buf(info, buf, &leng);
	if (k == -1 || (k == 0 && leng == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	if (c != NULL){
		sl = 1 + (unsigned int)(c - buf); /*calculate length*/
	}
	else
	{
		sl = leng; /*entire length of buf */
	}
	new_pro = _realloc(p, sl, sl ? sl + l : l + 1);
	if (!new_pro) /* malloc failure! */
		return (p ? free(p), -1 : -1);

	if (sl)
		_strncat(new_pro, buf + i, l - i);
	else
		_strncpy(new_pro, buf + i, l - i + 1);

	sl += l - i;
	i = l;
	p = new_pro;

	if (length)
		*length = sl;
	*ptr = p;
	return (sl); i }

/**
 * inp_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @leng: address of len var
 *
 * Return: bytes read
 */
ssize_t inp_buf(info_st *info, char **buf, size_t *leng)
{
	ssize_t n = 0;
	size_t len_p = 0;

	if (!*leng) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL; /*free it and set to null */
		signal(SIGINT, sigint_handler());

		n = _getline(info, buf, &len_p);

		if (n > 0)
		{
			if ((*buf)[n - 1] == '\n')
			{
				(*buf)[n - 1] = '\0'; /* remove trailing newline */
				n--;
			}
			/*info->linecount_flag = 1;*/
			remove_comments(*buf);/*remove comments from input */

			if (_strchr(*buf, ';')) /*is this a command chain? */
			{
				*leng = n;
				info->cmd_buf = buf; /*store the buffer in cmd_buf */
			}
		}
	}
	return (n);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_st *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, leng;
	ssize_t rn = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	rn = input_buf(info, &buf, &leng);
	if (rn == -1) /* EOF */
		return (-1);
	if (leng)	/* we have commands left in the chain buffer */
	{
		j = i; /* initlize new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, leng);
		while (j < leng) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= leng) /* reached end of buffer? */
		{
			i = leng = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (rn); /* return length of buffer from _getline() */
}
/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: reb
 */
ssize_t read_buf(info_st *info, char *buf, size_t *i)
{
	ssize_t reb = 0;

	if (*i)
		return (0);
	reb = read(info->readfd, buf, READ_BUF_SIZE);
	if (reb >= 0)
		*i = reb;
	return (reb);
}
void sigint_handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

