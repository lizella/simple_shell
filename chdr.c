#include "shell.h"
/**
 * _exit - exits shell
 * @passinfo: Struct
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int Shexit(info_t *passinfo)
{
	int exit;

	if (passinfo->argv[1]) /* If there is an exit arguement */
	{
		exit = _erratoi(passinfo->argv[1]);
		if (exit == -1)
		{
			info->status = 2;
			print_error(passinfo, "Illegal number: ");
			_eputs(passinfo->argv[1]);
			_eputchar('\n');
			return (1);
		}
		passinfo->err_num = _erratoi(passinfo->argv[1]);
		return (-2);
	}
	passinfo->err_num = -1;
	return (-2);
}
/**
 * _currentDr - current directory of the process
 * @passinfo: Struct
 * Return: Always 0
 */
int _currentDr(info_t *passinfo)
{
	char *data, *dr, buffer[1024];
	int num;

	data = getcwd(buffer, 1024);
	if (!data)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!passinfo->argv[1])
	{
		dr = _getenv(passinfo, "HOME=");
		if (!dr)
			num = /* TODO: what should this be? */
				chdir((dr = _getenv(passinfo, "PWD=")) ? dr : "/");
		else
			num = chdir(dr);
	}
	else if (_strcmp(passinfo->argv[1], "-") == 0)
	{
		if (!_getenv(passinfo, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(passinfo, "OLDPWD=")), _putchar('\n');
		num = /* TODO: what should this be? */
			chdir((dr = _getenv(passinfo, "OLDPWD=")) ? dr : "/");
	}
	else
		num = chdir(passinfo->argv[1]);
	if (num == -1)
	{
		print_error(passinfo, "can't cd to ");
		_eputs(passinfo->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(passinfo, "OLDPWD", _getenv(passinfo, "PWD="));
		_setenv(passinfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * changeDr - changes the current directory
 * @passinfo: Struct
 * Return: Always 0
 */
int changeDr(info_t *passinfo)
{
	char **arg_array;

	arg_array = passinfo->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

