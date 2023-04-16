#include "main.h"
/**
 * main - Entry point
 * @argc: argument counter
 * @argv: argument vector
 * @envp: environment
 *
 * Return: 0 on success otherwise on Error
 */

int main(int argc, char *argv[], char *envp[])
{
	char *buffer = NULL, *str, *arg[2];
	size_t size = 0;
	int i, get, ret;

	while (1)
	{
		printf("#cisfun$ ");
		get = getline(&buffer, &size, stdin);
		if (get == -1)
		{
			free(buffer);
			return (1);
		}
		str = strtok(buffer, "\n");
		while (str != NULL)
		{
			arg[0] = str;
			arg[1] = NULL;
			ret = fork();
			if (ret == -1)
				perror("");
			else if (ret == 0)
			{
				if (execve(str, arg, envp) == -1)
				{
					perror("./s");
					free(buffer);
					return (1);
				}
			}
			else
				wait(NULL);
			str = strtok(NULL, "\n");
		}
	}
	free(buffer);
	return (0);
}
