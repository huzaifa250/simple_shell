#include "shell.h"
/**
 * main - Entery point of program
 *
 * Return: 0 on success
 */
int main(void)
{
	char *buffer = NULL; /*storage size */
	char **av = NULL; /*arr of str or command */
	ssize_t ex; /*int exit_status = 0;*/

	while (1)
	{
		prompt();
		buffer = _read();/*read input enter by us */
		if (*buffer != '\0')
		{
			av = tokenize(buffer);
			if (av == NULL)/*if tokenize faill */
			{
				free(buffer);
				continue;
			}
			/**
			 * fullpathbuffer = _pathbuffer(av, PATH, copy);
			 * if (checkbuiltins(av, buffer, exitstatus) == 1)
			 * continue;
			 * exitstatus = _forkprocess(av, buffer, fullpathbuffer);
			 **/
		}
		else
			free(buffer);
	}
	return (0);
}
