#include "main.h"

/**
 * check_path - check path
 * @command: the command to be checked
 *
 * Return: NULL or fpath
 */
char *check_path(char *command)
{
	char *path = NULL, *p, *fpath = NULL, *directory;
	int len;

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}
	if (access(command, X_OK) == 0)
		return (strdup(command));
	path = getenv("PATH");

	if (path == NULL)
	{
		return (NULL);
	}

	p = path = strdup(path);
	while ((directory = strsep(&p, ":")) != NULL)
	{
		len = strlen(directory) + strlen(command) + 2;
		fpath = malloc(len);
		if (fpath == NULL)
		{
			return (NULL);
		}
		snprintf(fpath, len, "%s/%s", directory, command);
		if (access(fpath, X_OK) == 0)
		{
			free(path);
			return (fpath);
		}
		free(fpath);
	}
	free(path);
	return (NULL);
}

