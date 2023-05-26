#include "shell.h"

/**
 * bfree - Free pointer
 * @ptr: Address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
		return 0; /* Invalid pointer or already NULL */

	free(*ptr);
	*ptr = NULL;
	return 1; /* Freed successfully */
}
