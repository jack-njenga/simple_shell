#include "main.h"

int my_setenv(const char *name, const char *value)
{
    if (name == NULL || value == NULL || strchr(name, '=') != NULL)
    {
        fprintf(stderr, "Invalid arguments\n");
        return (-1);
    }

    int ret = setenv(name, value, 1);
    if (ret != 0)
    {
        perror("setenv");
        return (-1);
    }

    return (0);
}

int my_unsetenv(const char *name)
{
    if (name == NULL || strchr(name, '=') != NULL)
    {
        fprintf(stderr, "Invalid arguments\n");
        return (-1);
    }

    int ret = unsetenv(name);
    if (ret != 0)
    {
        perror("unsetenv");
        return (-1);
    }

    return (0);
}
