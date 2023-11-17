#include "shell.h"
/**
 * main - Entery point of program
 *
 * Return: 0 on success
 */
int main(void)
{
	char *buffer = NULL, *copy = NULL; /*storage size */
	char **av; /*arr of str or command */
	char *Fullpathbuffer = NULL, *PATH = NULL;
	int exit_status = 0;

	signal(SIGINT, SIG_IGN);
	PATH = _getenv("PATH");
	if (PATH == NULL)
		return (-1);

	while (1)
	{
		av = NULL;
		prompt();
		buffer = _read();/*read input enter by us */
		if (*buffer != '\0')
		{
			av = tokenizer(buffer);
			if (av == NULL)/*if tokenize faill */
			{
				free(buffer);
				continue;
			}

			Fullpathbuffer = _pathbuffer(av, PATH, copy);
			if (checkbuiltin(av, buffer, exit_status) == 1)
				continue;
			 exit_status = fork_process(av, buffer, Fullpathbuffer);

		}
		else
			free(buffer);
	}
	return (0);

}

