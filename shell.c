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
	size_t size = 0, get, ret;
	int i;

	while (1)
	{
		printf("#cisfun$ ");
		get = getline(&buffer, &size, stdin);
		if (get == -1)
		{
			perror(":");
			return (1);
		}
		str = strtok(buffer, " \n");

		while (str != NULL)
		{
			arg[0] = str;
			arg[1] = NULL;
		
			if (i == 1)
			{
				break;
			}
			ret = fork();
			if (ret == -1)
			{
				perror("");
			}
			else if (ret == 0)
			{
				if (execve(str, arg, envp) == -1)
				{
					perror("");
				}
			}
			else
			{
				wait(NULL);
			}
			
			i++;
			free(buffer);
			buffer = NULL;
			size = 0;
			str = strtok(NULL, " \n");
		}
	}

	printf("DONE");
	free(buffer);
	return (0);

}
