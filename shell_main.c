#include "main.h"
/**
 * main - Entry point of the program(simple shell)
 *
 * Return: 0 on success else on error.
 */
int main(void)
{
	char *buffer = NULL, *args[64], *fpath, *del = " ";
	size_t size = 0;
	int i, status;

	while (true)
	{
		write(STDOUT_FILENO, "cisfun$ ", 8);
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
			args[i] = strtok(buffer, del);
			while (args[i] != NULL)
				args[++i] = strtok(NULL, del);
			if (check_keyword(args) == 0)
				free_exit(buffer);
			else
			{
				fpath = check_path(args[0]);
				if (fpath != NULL)
				{
					_fork(fpath, args, environ, &status);
					free(fpath);
				}
				else
					_free(fpath, args[0]);
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
 *
 * Return: 0 on success else on error
 */
int check_keyword(char *args[])
{

	if (strcmp(args[0], "exit") == 0)
	{
		return (0);
	}

	return (-1);
}

/**
 * _free - frees the fpath memory and prints the error
 * @fpath: the memory to free
 * @args: the string to print the error with
 *
 * Return: void.
 */
void _free(char *fpath, char *args)
{
	perror(args);
	free(fpath);
}

/**
 * free_exit - frees the buffer and exits
 * @buffer: buffer to free
 *
 * Return: void
 */
void free_exit(char *buffer)
{
	free(buffer);
	exit(0);
}
