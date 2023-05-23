#include "shell.h"
/**
 * Current_env - current environment
 * @info: Struct
 * Return: Always 0
 */
int Current_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * Env_vrb - gets the value of an environ variable
 * @info: Struct
 * @nm: env var name
 * Return: the value
 */
char *Env_vrb(info_t *info, const char *nm)
{
	list_t *node = info->env;
	char *num;

	while (node)
	{
		num = starts_with(node->str, nm);
		if (num && *num)
			return (num);
		node = node->next;
	}
	return (NULL);
}

/**
 * New_Env_Vrb - Initialize a new environment variable
 * @info: Struct
 *  Return: Always 0
 */
int New_Env_Vrb(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * Rmv_Evrb - Remove an environment variable
 * @info: Struct
 * Return: Always 0
 */
int Rmv_Evrb(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * Populate_Llist - populates env linked list
 * @info: Struct
 * Return: Always 0
 */
int Populate_Llist(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

