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
	char *buffer = NULL;
	size_t size = 0;
	int status;
	struct stat bf;

	while (true)
	{
		prompt(STDIN_FILENO, bf);
		if (_getline(&buffer, &size, stdin) == -1)
		{
			free(buffer);
			fstat(STDIN_FILENO, &bf);
			if (S_ISCHR(bf.st_mode))
				_puts("\n");
			exit(0);
		}
		buffer[strcspn(buffer, "\n")] = '\0';
		if (strlen(buffer) > 0)
		{
			process_buffer(buffer, argv[0], &status);
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
	int ret_exe;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		ret_exe = execve(full_path, args, env);
		if (ret_exe == -1)
		{
			if (errno == ENOENT)
				exit(2);
			perror("execve");
			exit(2);
		}
		else if (WIFEXITED(ret_exe) && WEXITSTATUS(ret_exe) != 0)
		{
			perror(args[0]);
			exit(2);
		}
	}
	else
	{
		wait(st);
		if (WIFSIGNALED(*st))
		{
			printf("child terminated by signal %d\n", WTERMSIG(*st));
			exit(2);
		}
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
		exit(0);
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
	if (!S_ISCHR(buf.st_mode))
		_puts("\n");
	n++;
	free(fpath);
	exit(127);
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
