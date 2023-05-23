#include "shell.h"
/**
 * S_prnts - prints a string
 * @s: the string 
 * Return: Nothing
 */
void S_prnts(char *s)
{
	int z = 0;

	if (!s)
		return;
	while (s[z] != '\0')
	{
		_errp(s[z]);
		z++;
	}
}
/**
 * _errp - writes  c to stderr
 * @num: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _errp(char num)
{
	static int z;
	static char buf[WRITE_BUF_SIZE];

	if (num == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(2, buf, z);
		z = 0;
	}
	if (num != BUF_FLUSH)
		buf[z++] = num;
	return (1);
}

/**
 * _wrtfls - writes the character c to given filedescriptor
 * @num: The character to print
 * @fls: The filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _wrtfls(char num, int fls)
{
	 int z;
	static char buf[WRITE_BUF_SIZE];

	if (num == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(fls, buf, z);
		z = 0;
	}
	if (num != BUF_FLUSH)
		buf[z++] = num;
	return (1);
}

/**
 * _fls - prints string
 * @str: the string to be printed
 * @fls: the filedescriptor to write to
 * Return: the number of chars put
 */
int _fls(char *str, int fls)
{
	int z = 0;

	if (!str)
		return (0);
	while (*str)
	{
		z += _putfd(*str++, fls);
	}
	return (z);
}

