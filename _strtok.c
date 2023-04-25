#include "main.h"

/*
 * tokenize - works like strtok to separate a string using delimiter
 * @buffer: input string to be tokenized
 * @delim: delimiter
 *
 * Return: tokenized string
 */

char *tokenize(char *buffer, char *delim)
{
	int j;
	static char *str;
	char *strcpy;

	if (buffer != NULL)
		str = buffer;
			for (; *str != '\0'; str++)
			{
				for (j = 0; delim[j] != '\0'; j++)
				{
					if (*str == delim[j])
						break;
				}
				if (delim[j] == '\0')
					break;
			}
			strcpy = str;
			if (*strcpy == '\0')
				return (NULL);
			for (; *str != '\0'; str++)
			{
				for (j = 0; delim[j] != '\0'; j++)
				{
					if (*str == delim[j])
					{
						*str = '\0';
						str++;
						return (strcpy);
					}
				}
			}
			return (strcpy);
}
