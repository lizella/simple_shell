#include "shell.h"

/**
 * freed - Free a pointer and set the address to NULL
 * @ptr: Address of the pointer to free
 *
 * Return: 1 if the pointer was freed, otherwise 0
 */
int freed(void **ptr)
{
	if (ptr != NULL && *ptr != NULL) {
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return 0;
}
