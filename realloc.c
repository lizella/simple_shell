#include "shell.h"

/**
 * _memset - Fill memory with a constant byte
 * @s: Pointer to the memory area
 * @b: Byte to fill *s with
 * @n: Amount of bytes to be filled
 * Return: Pointer to the memory area(s)
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}

	return (s);
}

/**
 * forfree - Free a string of strings
 * @pp: String of strings
 */
void forfree(char **pp)
{
	char **c = pp;

	if (!pp)
		return;

	while (*pp)
	{
		free(*pp);
		pp++;
	}

	free(c);
}

/**
 * _realloc - Reallocate a block of memory
 * @ptr: Pointer to previous block
 * @old_size: Byte size of previous block
 * @new_size: Byte size of new block
 * Return: Pointer to old block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (p);
}
