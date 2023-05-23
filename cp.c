#include "shell.h"
/**
 **_scp - copies  string
 *@d: the destination string to be copied to
 *@s: the source string
 *@num: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_scp(char *d, char *s, int num)
{
	int z, y;
	char *data = d;

	z = 0;
	while (s[z] != '\0' && z < num - 1)
	{
		d[z] = s[z];
		z++;
	}
	if (z < num)
	{
		y = z;
		while (y < num)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (data);
}

/**
 **_concat - concatenates two strings
 *@a: the first string
 *@b: the second string
 *@num: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_concat(char *a, char *b, int num)
{
	int z, x;
	char *y = dest;

	z = 0;
	x = 0;
	while (a[z] != '\0')
		z++;
	while (b[x] != '\0' && x < num)
	{
		a[z] = b[x];
		z++;
		x++;
	}
	if (x < num)
		a[z] = '\0';
	return (y);
}

/**
 **_loch - locates a character in a string
 *@a: the string to be parsed
 *@ch: the character to look for
 *Return:  a pointer to the memory area z
 */
char *_loch (char *a, char ch)
{
	do {
		if (*a == ch)
			return (z);
	} while (*z++ != '\0');

	return (NULL);
}

