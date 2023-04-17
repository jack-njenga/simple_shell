#include "main.h"
/**
 */
int argument(char *buffer, char *dell, char *envp[])
{
	char *arg[4], *str;
	int i = 0, ret;

	str = strtok(buffer, dell);
	while (str != NULL)
	{
		arg[i] = str;
		i++;
		str = strtok(NULL, dell);
	}
	arg[i] = NULL;
	ret = fork();
	if (ret == -1)
	{
		perror("");
	}
	else if (ret == 0)
	{
		if (execve(arg[0], arg, envp) == -1)
		{
			perror("./s");
			free(buffer);
			return (1);
		}
	}
	else
		wait(NULL);

}
