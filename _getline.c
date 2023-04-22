#include "main.h"

int add_space(char **buffer, size_t *size);

/**
 * _getline - this function is a version of
 * getline that reads from the input stream.
 * @buffer: the memory to store what the functon reads.
 * @size: the size of memory to allocate.
 * @stream: the type of stream to read from.
 *
 * Return: returns the number of character read or -1 on error
 */

ssize_t _getline(char **buffer, size_t *size, FILE *stream)
{
	static char buff[1024];
	static size_t buff_len;
	static size_t buff_pos;
	size_t len = 0;

	if (*buffer == NULL || *size == 0)
	{
		*size = 1024;
		*buffer = malloc(*size);
		if (*buffer == NULL)
			return (-1);
	}
	while (true)
	{
		if (buff_pos >= buff_len)
		{
			buff_len = read(fileno(stream), buff, sizeof(buff));
			buff_pos = 0;
			if (buff_len == 0)
				break;
		}
		if (len + 1 >= *size)
		{
			if (add_space(buffer, size) == -1)
				return (-1);
		}
		(*buffer)[len++] = buff[buff_pos++];
		if ((*buffer)[len - 1] == '\n')
			break;
	}
	(*buffer)[len] = '\0';
	if (len == 0)
		return (-1);
	return (len);
}
/**
 * add_space - this function resizes the allocated
 * memory if the original one can't hold the data
 * @buffer: a pointer to a pointer to the original allocated memory.
 * @size: size of memory to allocate.
 *
 * Return: -1 on error 0 on success.
 */

int add_space(char **buffer, size_t *size)
{
	char *new_buffer;
	size_t i;

	*size *= 2;
	new_buffer = malloc(*size);
	if (!new_buffer)
	{
		perror("malloc");
		return (-1);
	}
	for (i = 0; i < *size / 2; i++)
	{
		new_buffer[i] = (*buffer)[i];
	}

	free(*buffer);
	*buffer = new_buffer;

	return (0);
}
