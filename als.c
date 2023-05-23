#include "shell.h"

/**
 * _hist - history list
 * @info: Struct
 *  Return: Always 0
 */
int _hist(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * set_als - unsets alias to string
 * @info: struct
 * @st: the string 
 * Return: Always 0 on success, 1 on error
 */
int set_als(info_t *info, char *st)
{
	char *num, data;
	int otp;

	num = _strchr(str, '=');
	if (!num)
		return (1);
	data = *num;
	*num = 0;
	otp = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, st, -1)));
	*num = data;
	return (otp);
}

/**
 * set_als1 - sets alias to string
 * @info: struct
 * @st: the string 
 * Return: Always 0 on success, 1 on error
 */
int set_als1(info_t *info, char *st)
{
	char *num;

	num = _strchr(st, '=');
	if (!num)
		return (1);
	if (!*++num)
		return (set_als(info, st));

	set_als(info, st);
	return (add_node_end(&(info->alias), st, 0) == NULL);
}

/**
 * printAls - prints alias string
 * @n: node
 * Return: Always 0 on success, 1 on error
 */
int printAls(list_t *n)
{
	char *num = NULL, *data = NULL;

	if (n)
	{
		num = _strchr(n->str, '=');
		for (data = node->str; data <= num; data++)
		_putchar(*data);
		_putchar('\'');
		_puts(num + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _Als - alias builtin
 * @info: Struct
 *  Return: Always 0
 */
int _Als(info_t *info)
{
	int i = 0;
	char *num = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		num = _strchr(info->argv[i], '=');
		if (num)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

