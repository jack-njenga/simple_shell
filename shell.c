#include "main.h"
/**
 * main - Entry point
 * @argc: argument counter
 * @argv: argument vector
 * @envp: environment
 * Return: 0 on success otherwise on Error
 */

int main(int argc, char *argv[], char *envp[])
{
	char *buffer = NULL, *str, *arr[6], *dell = " \n";
	size_t size = 0;
	int i, get, ret, n = 0;
	char *env[] = {"PATH=/usr/local/bin:/usr/bin:/bin", NULL};

	printf("%s\n", envp[0]);
	while (1)
	{
		printf("#cisfun$ ");
		get = getline(&buffer, &size, stdin);
		if (get == -1)
			if (errno == EOF)
			{
				free(buffer);
				return (0);
			}
			else
			{
				free(buffer);
				return (1);
			}
		if (argument(buffer, dell, env) == 1)
		{
			return (1);
		}
		system("export PATH=$PATH:/bin/");
	}
	free(buffer);
	return (0);
}
