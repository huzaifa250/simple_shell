#include "shell.h"

/**
 * dell_info - initializes info_st struct
 * @info: struct address
 */
void dell_info(info_st *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * info_set - initializes info_st struct
 * @info: struct address
 * @av: argument vector
 */
void info_set(info_st *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		/*replace_alias(info);*/
		replace_vars(info);
	}
}

/**
 * info_free - frees info_st struct fields
 * @info: struct address
 * @all: freeing all fields
 */
void info_free(info_st *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
/*	if (info->history)
*			free_list(&(info->history));
*		if (info->alias)
*/			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

