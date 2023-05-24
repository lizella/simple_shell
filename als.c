#include "shell.h"
/**
 * _hist - history list
 * @passinfo: Struct
 *  Return: Always 0
 */
int _hist(info_t *passinfo)
{
	print_list(passinfo->history);
	return (0);
}

/**
 * set_als - unsets alias to string
 * @passinfo: struct
 * @st: the string 
 * Return: Always 0 on success, 1 on error
 */
int set_als(info_t *passinfo, char *st)
{
	char *num, data;
	int otp;

	num = _strchr(str, '=');
	if (!num)
		return (1);
	data = *num;
	*num = 0;
	otp = delete_node_at_index(&(passinfo->alias),
		get_node_index(passinfo->alias, node_starts_with(info->alias, st, -1)));
	*num = data;
	return (otp);
}

/**
 * set_als1 - sets alias to string
 * @passinfo: struct
 * @st: the string 
 * Return: Always 0 on success, 1 on error
 */
int set_als1(info_t *passinfo, char *st)
{
	char *num;

	num = _strchr(st, '=');
	if (!num)
		return (1);
	if (!*++num)
		return (set_als(passinfo, st));

	set_als(passinfo, st);
	return (add_node_end(&(passinfo->alias), st, 0) == NULL);
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
 * @passinfo: Struct
 *  Return: Always 0
 */
int _Als(info_t *passinfo)
{
	int i = 0;
	char *num = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = passinfo->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; passinfo->argv[i]; i++)
	{
		num = _strchr(passinfo->argv[i], '=');
		if (num)
			set_alias(passinfo, passinfo->argv[i]);
		else
			print_alias(node_starts_with(passinfo->alias, passinfo->argv[i], '='));
	}

	return (0);
}

