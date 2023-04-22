#include "main.h"

ssize_t _getline(char **buffer, size_t *size, FILE *stream)
{
    static char buff[1024];
    static size_t buff_len = 0;
    static size_t buff_pos = 0;
    size_t len = 0;
    int fd = fileno(stream);

    if (*buffer == NULL || *size == 0)
    {
        *size = 1024;
        *buffer = malloc(*size);
        if (*buffer == NULL)
        {
            perror("malloc");
            return -1;
        }
    }

    while (1)
    {
        if (buff_pos >= buff_len)
        {
            buff_len = read(fd, buff, sizeof(buff));
            buff_pos = 0;
            if (buff_len == 0)
                break;
        }

        if (len + 1 >= *size)
        {
            char *new_buffer;
            *size *= 2;
            new_buffer = malloc(*size);
            if (new_buffer == NULL)
            {
                perror("malloc");
                return -1;
            }
            for (size_t i = 0; i < len; i++)
            {
                new_buffer[i] = (*buffer)[i];
            }
            free(*buffer);
            *buffer = new_buffer;
        }

        (*buffer)[len++] = buff[buff_pos++];
        if ((*buffer)[len - 1] == '\n')
            break;
    }

    (*buffer)[len] = '\0';
    return (len == 0) ? -1 : len;
}
/*
int main(void)
{
	char *buff = NULL;
	size_t size = 0;

	_getline(&buff, &size, stdin);

	printf("buff has : %s\n", buff);
	printf("len @ buff : %ld\n", strlen(buff));

	free(buff);
	return (0);
}
*/
