#include "main.h"
/**
 * _getline - this function is a version of
 * getline that reads from the input stream.
 * @buffer: the memory to store what the functon reads.
 * @size: the size of memory to allocate.
 * @stream: the type of stream to read from.
 * Return: returns the number of character read or -1 on error
 */
ssize_t _getline(char **buffer, size_t *size, FILE *stream)
{
	static char buff[1024];
	static size_t buff_len;
	static size_t buff_pos;
	size_t len = 0, i;
	char *new_buff;

	if (!buffer || !size || !stream)
		return (-1);

	if (*buffer == NULL || *size == 0)
	{
		*size = 1024;
		*buffer = malloc(*size);
		if (*buffer == NULL)
		{
			perror("malloc");
			return (-1);
		}
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
			*size *= 2;
			new_buff = malloc(*size);
			if (new_buff == NULL)
			{
				perror("malloc");
				return (-1);
			}
			for (i = 0; i < len; i++)
				new_buff[i] = (*buffer)[i];

			free(*buffer);
			*buffer = new_buff;
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
