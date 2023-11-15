#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_st *info, char *path)
{
	struct stat stinfo; /*store file info */

	(void)info;
	if (!path || stat(path, &stinfo)) /*check if path is null */
		return (0); /*indicate file isn't executable comm */

	if (stinfo.st_mode & S_IFREG) /*check is regular file */
	{
		return (1);
	}
	return (0);

/**
 * dup_chars - duplicates characters from a specified range
 * @pathstr: PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	char *buf = NULL;/*to store duplicate chars */
	int i = 0, j = 0;

	buf = malloc((stop - start + 1) * sizeof(char));
	if (buf == NULL)
		return;

	for (j = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[j++] = pathstr[i]; /*copy */
	buf[j] = '\0';
	return (buf);
}

/**
 * f_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string searching
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *f_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, cur_pors = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, cur_pors, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			cur_pors = i;
		}
		i++;
	}
	return (NULL);
}

