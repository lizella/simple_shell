#include "shell.h"
/**
 * _exit - exits shell
 * @info: Struct
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _exit(info_t *info)
{
	int exit;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exit = _erratoi(info->argv[1]);
		if (exit == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * _currentDr - current directory of the process
 * @info: Struct
 * Return: Always 0
 */
int _currentDr(info_t *info)
{
	char *data, *dr, buffer[1024];
	int num;

	data = getcwd(buffer, 1024);
	if (!data)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dr = _getenv(info, "HOME=");
		if (!dr)
			num = /* TODO: what should this be? */
				chdir((dr = _getenv(info, "PWD=")) ? dr : "/");
		else
			num = chdir(dr);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		num = /* TODO: what should this be? */
			chdir((dr = _getenv(info, "OLDPWD=")) ? dr : "/");
	}
	else
		num = chdir(info->argv[1]);
	if (num == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * changeDr - changes the current directory 
 * @info: Struct
 * Return: Always 0
 */
int changeDr(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

