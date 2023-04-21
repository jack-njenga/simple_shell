#include "main.h"

/**
 *
 */
int main(__attribute__((unused)) int ac, __attribute__((unused)) char *arg[], char *envp[])
{
	char *buffer = NULL, *args[64];
	size_t size = 0;
	int i;
	char *del = " ";
	char *fpath;
	pid_t pid;
	int status;

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
			{
				i++;
				args[i] = strtok(NULL, del);
			}
			if (strcmp(args[0], "exit") == 0)
			{
				free(buffer);
				exit(0);
			}
			if (strcmp(args[0], "env") == 0)
			{
				for (i = 0; envp[i] != NULL; i++)
				{
					write(STDOUT_FILENO, envp[i], strlen(envp[i]));
					write(STDOUT_FILENO, "\n", 1);
				}
			}
			else
			{
				fpath = check_path(args[0]);
				if (fpath != NULL)
				{
					pid = fork();
					if (pid == 0)
					{
						if (execve(fpath, args, envp) == -1)
						{
							perror("EXECVE");
							exit(1);
						}
					}
					else
					{
						wait(&status);
					}
					free(fpath);
				}
				else
				{
					perror(args[0]);
					free(fpath);
				}
			}
		}
	}
	free(buffer);
	return (0);
}
