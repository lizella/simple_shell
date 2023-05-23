#include "shell.h"

/**
 * is_chain - Test if current char in buffer is a chain delimiter
 * @info: Parameter struct
 * @buf: Char buffer
 * @p: Address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;
	int is_delimiter = 0;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
		is_delimiter = 1;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
		is_delimiter = 1;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
		is_delimiter = 1;
	}

	*p = j;
	return (is_delimiter);
}

/**
 * check_chain - Check whether chaining should continue
 * @info: Parameter struct
 * @buf: Char buffer
 * @p: Address of current position in buf
 * @i: Starting position in buf
 * @len: buf lenght
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND && info->status)
	{
		buf[i] = 0;
		j = len;
	}

	if (info->cmd_buf_type == CMD_OR && !info->status)
	{
		buf[i] = 0;
		j = len;
	}

	*p = j;
}

/**
 * rep_alias - Replace an alias in the tokenized string
 * @info: Parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);

		p = _strdup(p + 1);
		if (!p)
			return (0);

		info->argv[0] = p;
	}

	return (1);
}

/**
 * rep_vars - Replace variables in the tokenized string
 * @info: Parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			rep_string(&(info->argv[i]), _strdup(convert_number(info->status, 10, 0)));
			continue;
		}

		if (!_strcmp(info->argv[i], "$$"))
		{
			rep_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}

		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			rep_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}

		rep_string(&info->argv[i], _strdup(""));
	}

	return (0);
}

/**
 * rep_string - Replaces string
 * @old: Address of old string
 * @new: New string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
