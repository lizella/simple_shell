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

	/* Copy characters from source to destination */
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
 * @str: String to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	/* Copy characters from source to destination in reverse order */
	for (length++; length--;)
		ret[length] = *--str;

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

	/* Print each character of the string */
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Write character to output.
 * @c: Character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	/* Flush buffer and reset index if buffer is full or requested */
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	/* Add character to buffer unless it's a flush request */
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}
