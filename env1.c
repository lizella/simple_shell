#include "shell.h"
/**
 * env1 - returns the string array copy of our environ
 * @info: Struct
 * Return: Always 0
 */
char **env1(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}
/**
 * _uEnv - Remove an environment variable
 * @info: Struct
 *  Return: 1 on delete, 0 otherwise
 * @v: the string env var property
 */
int _uEnv(info_t *info, char *v)
{
	list_t *node = info->env;
	size_t z = 0;
	char *x;

	if (!node || !v)
		return (0);

	while (node)
	{
		x = starts_with(node->str, v);
		if (x && *x == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), z);
			z = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		z++;
	}
	return (info->env_changed);
}

/**
 * _newVar - Initialize a new environment variable
 * @info: Struct
 * @v: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _newVar(info_t *info, char *v, char *val)
{
	char *buf = NULL;
	list_t *node;
	char *z;

	if (!v || !val)
		return (0);

	buf = malloc(_strlen(v) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, v);
	_strcat(buf, "=");
	_strcat(buf, val);
	node = info->env;
	while (node)
	{
		z = starts_with(node->str, v);
		if (z && *z == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

