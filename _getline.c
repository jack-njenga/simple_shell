#include "main.h"
/**
 */
ssize_t _getline(char **buffer, size_t *size, FILE *stream)
{
	char buff[1024];
	ssize_t ret;
	int fd;
	static int sz = 0;

	sz = sizeof(buff);
	fd = fileno(stream);
	ret = read(fd, buff, sz);

	//printf("buff len = %ld\n", strlen(buff));

	*buffer = malloc(strlen(buff) + 1);
	if (*buffer == NULL)
	{
		perror("malloc");
		return (-1);
	}
	strcpy(*buffer, buff);

	if (ret == -1)
		perror("read");
	return (ret);
}
/*int main(void)
{
	char *buff = NULL;
	size_t size = 0;
	int ret;

	printf("ENTER $ ");
	ret = _getline(&buff, &size, stdin);

		//ret = _getline(&buff, &size, stdin);

	printf("return value = %d\n", ret);
	printf("===>> %s\n", buff);

	free(buff);
	return (0);
}*/

