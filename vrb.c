#include "shell.h"
/**
 * Current_env - current environment
 * @passinfo: Struct
 * Return: Always 0
 */
int Current_env(info_t *passinfo)
{
	print_list_str(passinfo->env);
	return (0);
}

/**
 * Env_vrb - gets the value of an environ variable
 * @passinfo: Struct
 * @nm: env var name
 * Return: the value
 */
char *Env_vrb(info_t *passinfo, const char *nm)
{
	list_t *node = passinfo->env;
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
 * @passinfo: Struct
 *  Return: Always 0
 */
int New_Env_Vrb(info_t *passinfo)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(passinfo, passinfo->argv[1], passinfo->argv[2]))
		return (0);
	return (1);
}

/**
 * Rmv_Evrb - Remove an environment variable
 * @passinfo: Struct
 * Return: Always 0
 */
int Rmv_Evrb(info_t *passinfo)
{
	int i;

	if (passinfo->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= passinfo->argc; i++)
		_unsetenv(passinfo, passinfo->argv[i]);

	return (0);
}

/**
 * Populate_Llist - populates env linked list
 * @passinfo: Struct
 * Return: Always 0
 */
int Populate_Llist(info_t *passinfo)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	passinfo->env = node;
	return (0);
}

