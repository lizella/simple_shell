#include "shell.h"

/**
 * _strcpy - Copy a string
 * @dest: Destination
 * @src: Source
 *
 * Return: Pointer to destination
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	if (dest == src || src == NULL)
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
 * _strdup - Duplicate a string
 * @str: String to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *c;

	if (str == NULL)
		return (NULL);

	while (str[length])
		length++;

	c = malloc(sizeof(char) * (length + 1));
	if (!c)
		return (NULL);

	for (int i = 0; i <= length; i++)
		c[i] = str[i];

	return (c);
}

/**
 * _puts - Prints an input string
 * @str: String to be printed
 *
 * Return: Nothing
 */
void _puts(const char *str)
{
	if (!str)
		return;

	int i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Write the character c to stdout
 * @c: Character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}