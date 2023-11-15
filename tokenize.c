
#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL when Fail
 */

char **strtow(char *str, char *d)
{
	int a, b, c, fm, numb_words = 0;
	char **cs;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			numb_words++;

	if (numb_words == 0)
		return (NULL);
	cs = malloc((1 + numb_words) * sizeof(char *));
	if (!cs)
		return (NULL);
	for (a = 0, b = 0; b < numb_words; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		cs[b] = malloc((c + 1) * sizeof(char));
		if (!cs[b])
		{
			for (fm = 0; fm < b; fm++)
				free(cs[fm]);
			free(cs);
			return (NULL);
		}
		for (fm = 0; fm < c; fm++)
			cs[b][fm] = str[a++];
		cs[b][fm] = 0;
	}
	cs[b] = NULL;
	return (cs);
}

/**
 * **strtow_2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow_2(char *str, char d)
{
	int ia, jb, kc, m, num_words = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (ia = 0; str[ia] != '\0'; ia++)
		if ((str[ia] != d && str[ia + 1] == d) ||
		    (str[ia] != d && !str[ia + 1]) || str[ia + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	st = malloc((1 + num_words) * sizeof(char *));
	if (!st)
		return (NULL);
	for (ia = 0, jb = 0; jb < num_words; jb++)
	{
		while (str[ia] == d && str[ia] != d)
			ia++;
		kc = 0;
		while (str[ia + kc] != d && str[ia + kc] && str[ia + kc] != d)
			kc++;
		st[jb] = malloc((kc + 1) * sizeof(char));
		if (!st[jb])
		{
			for (kc = 0; kc < jb; kc++)
				free(st[kc]);
			free(st);
			return (NULL);
		}
		for (m = 0; m < kc; m++)
			st[jb][m] = str[ia++];
		st[jb][m] = 0;
	}
	st[jb] = NULL;
	return (st);
}

