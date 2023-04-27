#include "main.h"
/**
 * prompt - checks mode and prints to it in interactive mode
 * @fd: file stream
 * @bf: structure buffer
 *
 * Return: void
 */
void prompt(int fd, struct stat bf)
{
	fstat(fd, &bf);

	if (S_ISCHR(bf.st_mode))
		_puts("#cisfun$ ");
}
/**
 * _puts - prints a string to the stdout
 * @str: string to print
 *
 * Return: void
 */
void _puts(char *str)
{
	write(STDOUT_FILENO, str, strlen(str));
}
