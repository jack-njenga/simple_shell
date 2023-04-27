#include "main.h"
/**
 * process_buffer - processes the buffer
 * @buffer: buffer to process
 * @argv0: first argument
 * @status: status pointer
 *
 * Return: void
 */
void process_buffer(char *buffer, char *argv0, int *status)
{
	char *args[64], *fpath, *del = " ";
	int i;

	i = 0;
	args[i] = tokenize(buffer, del);
	if (args[i] == NULL)
	{
		return;
	}
	while (args[i] != NULL)
		args[++i] = tokenize(NULL, del);
	if (check_keyword(args, buffer) == 0)
		free_exit(buffer, 2);
	else
	{
		fpath = check_path(args[0]);
		if (fpath != NULL)
		{
			_fork(fpath, args, environ, status);
			free(fpath);
		}
		else
			_free(fpath, argv0, args[0]);
	}
}
