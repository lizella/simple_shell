#include "shell.h"

/**
 * _strcpy - Copies a string.
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strdup - Duplicate a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (str[length])
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	for (int i = 0; i <= length; i++)
		ret[i] = str[i];

	return (ret);
}

/**
 * _puts - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i])
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Write character to the output
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i = 0;
	static char buf[WRITE_BUF_SIZE];

	if (c != BUF_FLUSH && i < WRITE_BUF_SIZE)
		buf[i++] = c;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	return (1);
}
