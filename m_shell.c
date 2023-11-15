
#include "shell.h"

/**
 * hash - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hash(info_st *info, char **av)
{
	ssize_t re = 0;
	int builtin_ret = 0;

	while (1)
	{
		dell_info(info);
		if (prompt(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		re = get_input(info);
		if (re != -1)
		{
			info_set(info, av);
			builtin_ret = f_builtin(info);
			if (builtin_ret == -1)
				f_cmd(info);
		}
		else if (prompt(info))
			_putchar('\n');
		info_free(info, 0);
	}
	info_free(info, 1);
	if (!prompt(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_st *info)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		/* PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			info_free(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

