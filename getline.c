#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_SIZE 1024

/**
 * _getline - reads an entire line from a file stream
 * @lineptr: a pointer to the buffer to read into
 * @n: a pointer to the size of the buffer
 * @stream: the file stream to read from
 * Return: the number of characters read, or -1 on error
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
    static char buffer[READ_SIZE];
    char *newptr;
    size_t i;
    ssize_t bytes;

    if (lineptr == NULL || n == NULL || stream == NULL)
        return (-1);
    if (*lineptr == NULL)
    {
        *lineptr = malloc(sizeof(char) * READ_SIZE);
        if (*lineptr == NULL)
            return (-1);
        *n = READ_SIZE;
    }
    for (i = 0; ; i += bytes)
    {
        bytes = read(fileno(stream), buffer, READ_SIZE);
        if (bytes == -1)
            return (-1);
        if (bytes == 0)
            break;
        if (i + bytes >= *n)
        {
            newptr = malloc(sizeof(char) * (*n + READ_SIZE));
            if (newptr == NULL)
                return (-1);
            for (size_t j = 0; j < i; j++)
                newptr[j] = (*lineptr)[j];
            free(*lineptr);
            *lineptr = newptr;
            *n += READ_SIZE;
        }
        for (size_t j = 0; j < bytes; j++)
            (*lineptr)[i + j] = buffer[j];
    }
    (*lineptr)[i] = '\0';
    return (i);
}
