#include "shell.h"

/**
 * add_node - Add node to start list.
 * @head: Address head node pointer
 * @str: New node.
 * @num: Node index
 *
 * Return: Pointer to the new node.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	if (!head)
		return NULL;

	list_t *new_head = malloc(sizeof(list_t));
	if (!new_head)
		return NULL;

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return NULL;
		}
	}

	new_head->next = *head;
	*head = new_head;

	return (new_head);
}

/**
 * add_node_end - Adds a node to the end of the list
 * @head: Address of pointer to head node.
 * @str: New node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the new node.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	if (!head)
		return NULL;

	list_t *new_node = malloc(sizeof(list_t));
	if (!new_node)
		return NULL;

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return NULL;
		}
	}

	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return new_node;
	}

	list_t *node = *head;
	while (node->next)
		node = node->next;

	node->next = new_node;

	return new_node;
}

/**
 * print_list_str - Print element of linked list
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(Nil)");
		_puts("\n");
		h = h->next;
		i++;
	}

	return i;
}

/**
 * delete_node_at_index - Deletes a node at index
 * @head: Address of pointer to the first node
 * @index: Index of the node to delete
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	if (!head || !*head)
		return 0;

	if (index == 0)
	{
		list_t *node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return 1;
	}

	list_t *prev_node = NULL;
	list_t *curr_node = *head;
	unsigned int i = 0;

	while (curr_node)
	{
		if (i == index)
		{
			prev_node->next = curr_node->next;
			free(curr_node->str);
			free(curr_node);
			return 1;
		}

		prev_node = curr_node;
		curr_node = curr_node->next;
		i++;
	}

	return 0;
}

/**
 * free_list - Free nodes of list
 * @head_ptr: Address of pointer to the head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	if (!head_ptr || !*head_ptr)
		return;

	list_t *node = *head_ptr;

	while (node)
	{
		list_t *next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}
