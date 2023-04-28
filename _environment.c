#include "main.h"

/**
 * my_setenv - function that sets env
 * @nm: name
 * @val: value
 *
 * Return: -1 on failure 0 on success
 */

int my_setenv(const char *nm, const char *val)
{
	int ret;

	if (nm == NULL || val == NULL || strchr(nm, '=') != NULL)
	{
		fprintf(stderr, "Invalid arguments\n");
		return (-1);
	}

	ret = setenv(nm, val, 1);
	if (ret != 0)
	{
		perror("setenv");
		return (-1);
	}

	return (0);
}

/**
 * my_unsetenv - function that unsets env
 * @nm: name
 *
 * Return: -1 on failure 0 on success
 */

int my_unsetenv(const char *nm)
{
	int ret;

	if (nm == NULL || strchr(nm, '=') != NULL)
	{
		fprintf(stderr, "Invalid arguments\n");
		return (-1);
	}

	ret = unsetenv(nm);
	if (ret != 0)
	{
		perror("unsetenv");
		return (-1);
	}

	return (0);
}
