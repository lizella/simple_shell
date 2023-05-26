#include "shell.h"

/**
 * list_len - Determine list length
 * @h: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		i++;
		h = h->next;
	}

	return (i);
}

/**
 * list_to_strings - Convert a linked list to array of strings
 * @head: Pointer to the first node
 *
 * Return: Array of strings.
 */
char **list_to_strings(list_t *head)
{
	size_t i, j;
	char **strs;
	char *str;
	list_t *node = head;

	if (!head || !list_len(head))
		return (NULL);

	strs = malloc(sizeof(char *) * (list_len(head) + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}

	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - Prints all elements of a list_t linked list
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");

		i++;
		h = h->next;
	}

	return (i);
}

/**
 * node_starts_with - Return the node prefix starting
 * @node: Pointer to the list head.
 * @prefix: String to match as a prefix
 * @c: The next character after the prefix to match
 *
 * Return: Matched node or NULL.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);

		node = node->next;
	}

	return (NULL);
}

/**
 * get_node_index - Gets the index of a node in a linked list
 * @head: Pointer to the list head
 * @node: Pointer to the node
 *
 * Return: Index of the node or -1 if not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);

		i++;
		head = head->next;
	}

	return (-1);
}
