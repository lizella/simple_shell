#include "shell.h"

/**
 * loop_through - Main shell loop
 * @passinfo: Parameter & return info struct
 * @av: Argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int loop_through(info_t *passinfo, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(passinfo);
		if (interactive(passinfo))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(passinfo);
		if (r != -1)
		{
			set_info(passinfo, av);
			builtin_ret = find_builtin(passinfo);
			if (builtin_ret == -1)
				find_cmd(passinfo);
		}
		else if (interactive(passinfo))
			_putchar('\n');
		free_info(passinfo, 0);
	}
	write_history(passinfo);
	free_info(passinfo, 1);
	if (!interactive(passinfo) && passinfo->status)
		exit(passinfo->status);
	if (builtin_ret == -2)
	{
		if (passinfo->err_num == -1)
			exit(passinfo->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Find a builtin command
 * @passinfo: Parameter and return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin(info_t *passinfo)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
	{
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			passinfo->line_count++;
			built_in_ret = builtintbl[i].func(passinfo);
			break;
		}
	}
	return (built_in_ret);
}

/**
 * find_cmd - Find a command in PATH
 * @passinfo: Parameter and return info struct
 *
 * Return: void
 */
void find_cmd(info_t *passinfo)
{
	char *path = NULL;
	int i, k;

	passinfo->path = passinfo->argv[0];
	if (passinfo->linecount_flag == 1)
	{
		passinfo->line_count++;
		passinfo->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
	{
		if (!is_delim(passinfo->arg[i], " \t\n"))
			k++;
	}
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		passinfo->path = path;
		fork_cmd(passinfo);
	}
	else
	{
		if ((interactive(passinfo) || _getenv(passinfo, "PATH=") || passinfo->argv[0][0] == '/') && is_cmd(passinfo, passinfo->argv[0]))
			fork_cmd(passinfo);
		else if (*(info->arg) != '\n')
		{
			passinfo->status = 127;
			print_error(passinfo, "Not found\n");
		}
	}
}

/**
 * fork_cmd - Forks an executable thread to run
 * @passinfo: Parameter and return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *passinfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(passinfo->path, passinfo->argv, get_environ(passinfo)) == -1)
		{
			free_info(passinfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(passinfo->status));
		if (WIFEXITED(passinfo->status))
		{
			passinfo->status = WEXITSTATUS(passinfo->status);
			if (passinfo->status == 126)
				print_error(passinfo, "Permission denied\n");
		}
	}
}

