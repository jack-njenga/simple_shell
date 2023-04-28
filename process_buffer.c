#include "main.h"
/**
 * process_buffer - processes the buffer
 * @buffer: buffer to process
 * @argv: first argument
 * @status: status pointer
 *
 * Return: void
 */
void process_buffer(char *buffer, char *argv, int *status)
{
	char *args[64], *fpath, *del = " ";
	int i, ret;

	i = 0;
	args[i] = tokenize(buffer, del);
	if (args[i] == NULL)
	{
		return;
	}
	while (args[i] != NULL)
		args[++i] = tokenize(NULL, del);
	ret = check_keyword(args, buffer, status, argv);
	if (ret == 0)
	{
		free_exit(buffer, *status);
	}
	if (ret == 1)
	{
		
	}
	else
	{
		fpath = check_path(args[0]);
		if (fpath != NULL)
		{
			_fork(fpath, args, environ, status);
			free(fpath);
		}
		else
			_free(fpath, argv, args[0], status);
	}
}
