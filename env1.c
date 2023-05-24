#include "shell.h"
/**
 * env1 - returns the string array copy of our environ
 * @passinfo: Struct
 * Return: Always 0
 */
char **env1(info_t *passinfo)
{
	if (!passinfo->environ || passinfo->env_changed)
	{
		passinfo->environ = list_to_strings(passinfo->env);
		passinfo->env_changed = 0;
	}

	return (passinfo->environ);
}
/**
 * _uEnv - Remove an environment variable
 * @passinfo: Struct
 *  Return: 1 on delete, 0 otherwise
 * @v: the string env var property
 */
int _uEnv(info_t *passinfo, char *v)
{
	list_t *node = passinfo->env;
	size_t z = 0;
	char *x;

	if (!node || !v)
		return (0);

	while (node)
	{
		x = starts_with(node->str, v);
		if (x && *x == '=')
		{
			passinfo->env_changed = delete_node_at_index(&(passinfo->env), z);
			z = 0;
			node = passinfo->env;
			continue;
		}
		node = node->next;
		z++;
	}
	return (passinfo->env_changed);
}

/**
 * _newVar - Initialize a new environment variable
 * @passinfo: Struct
 * @v: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _newVar(info_t *passinfo, char *v, char *val)
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
			passinfo->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	passinfo->env_changed = 1;
	return (0);
}

