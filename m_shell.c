
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
 * f_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int f_builtin(info_st *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", special_exit},
		//{"env", my_env},
		{"help", my_help},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", sp_cd},
		//{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * f_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: Nothing
 */
void f_cmd(info_st *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((prompt(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
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

