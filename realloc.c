#include "shell.h"

/**
 * _memset - Fills memory with a constant byte
 * @s: Pointer to the memory area
 * @b: Byte to fill
 * @n: Number of bytes to be filled
 *
 * Return: Pointer to the memory
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;

	return (s);
}

/**
 * ffree - Frees a string of strings.
 * @pp: String of strings.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;

	while (*pp)
	{
		free(*pp);
		pp++;
	}

	free(a);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the reallocated memory block.
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

	if (old_size < new_size)
		new_size = old_size;

	while (new_size--)
		p[new_size] = ((char *)ptr)[new_size];

	free(ptr);
	return (p);
}
