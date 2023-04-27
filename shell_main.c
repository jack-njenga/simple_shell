#include "main.h"
/**
 * main - Entry point of the program(simple shell)
 * @argc: argument counter.
 * @argv: argument vector.
 *
 * Return: 0 on success else on error.
 */
int main(__attribute__((unused)) int argc, char *argv[])
{
	char *buffer = NULL, *args[64], *fpath, *del = " ";
	size_t size = 0;
	int i, status;
	struct stat bf;

	while (true)
	{
		/*write(STDOUT_FILENO, "cisfun$ ", 8);*/
		prompt(STDIN_FILENO, bf);
		if (_getline(&buffer, &size, stdin) == -1)
		{
			free(buffer);
			write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}
		buffer[strcspn(buffer, "\n")] = '\0';
		if (strlen(buffer) > 0)
		{
			i = 0;
			args[i] = tokenize(buffer, del);
			while (args[i] != NULL)
				args[++i] = tokenize(NULL, del);
			if (check_keyword(args, buffer) == 0)
				free_exit(buffer, 0);
			else
			{
				fpath = check_path(args[0]);
				if (fpath != NULL)
				{
					_fork(fpath, args, environ, &status);
					free(fpath);
				}
				else
					_free(fpath, argv[0], args[0]);
			}
		}
	}
	free(buffer);
	return (0);
}

/**
 * _fork - create a new process;
 * @full_path: the files full path.
 * @args: arguments for the command
 * @env: environment variables
 * @st: status of the child process
 *
 * Return: void
 */
void _fork(char *full_path, char *args[], char *env[], int *st)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		if (execve(full_path, args, env) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		wait(st);
	}
}
/**
 * check_keyword - checks for a certain keyword
 * @args: an array of strings to search for the keyword
 * @buffer: the buffer to free.
 * Return: 0 on success else on error
 */
int check_keyword(char *args[], char *buffer)
{
	int status;

	if (strcmp(args[0], "exit") == 0)
	{
		if (args[1] != NULL)
		{
			status = atoi(args[1]);
			free_exit(buffer, status);
		}
		return (0);
	}

	return (-1);
}

/**
 * _free - frees the fpath memory and prints the error
 * @fpath: the memory to free
 * @ar: the string to print the error with
 * @arg: the command.
 *
 * Return: void.
 */
void _free(char *fpath, char *ar, char *arg)
{
	static int n = 1;
	struct stat buf;

	/*perror(ar);*/
	fprintf(stderr, "%s: %d: %s: not found", ar, n, arg);

	fstat(STDIN_FILENO, &buf);
	if (S_ISCHR(buf.st_mode))
	{
		_puts("\n");
	}
	n++;
	free(fpath);
}

/**
 * free_exit - frees the buffer and exits
 * @buffer: buffer to free
 * @status: integer passed to exit call
 *
 * Return: void
 */
void free_exit(char *buffer, int status)
{
	free(buffer);
	exit(status);
}
