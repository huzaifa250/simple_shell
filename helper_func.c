#include "shell.h"
/**
 * _strdup - duplicates a string
 * @s: pointer to string to duplicate
 *
 * Return: pointer to duplicated string
 */
char *_strdup(char *s)
{
	int i;
	char *dest;

	if (s == NULL)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		;
	dest = malloc(sizeof(char) * (i + 1));
	if (dest == NULL)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
	{
		dest[i] = s[i];
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * split_string - counts number of words in string
 * @str: pointer to string to count
 *
 * Return: number of words in string
 */
int split_string(char *str)
{
	int i;
	int search_flag = 1;
	int word_coun = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] != ' ' && search_flag == 1)
		{
			word_coun += 1;
			search_flag = 0;
		}
		if (str[i + 1] == ' ')
			search_flag = 1;
	}
	return (word_coun);
}
/**
 * _strlen - returns the length of a string.
 * @s: argument of type string.
 * Return: length of a string.
 */
int _strlen(char *s)
{
	int length = 0;

	while (*(s + length) != '\0')
		length++;
	return (length);
}
/**
 * _strcat - function concatenates srtings
 * @dest: param pointer to a char
 * @src: param pointer to a char
 * Return: return value of dest
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	j = 0;

	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
