#include "shell.h"
/**
 * _crtStoInt - converts  string to  integer
 * @data: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _crtStoInt(char *data)
{
	int z = 0;
	unsigned long int result = 0;

	if (*data == '+')
		data++; 
	for (z = 0;  data[z] != '\0'; z++)
	{
		if (data[z] >= '0' && data[z] <= '9')
		{
			result *= 10;
			result += (data[z] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _rtnEr - prints an error message
 * @passinfo: the parameter & return info struct
 * @der: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void _rtnEr(info_t *passinfo, char *der)
{
	_eputs(passinfo->fname);
	_eputs(": ");
	print_d(passinfo->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(passinfo->argv[0]);
	_eputs(": ");
	_eputs(der);
}
/**
 * _dec - function prints a decimal (integer) number (base 10)
 * @num: the input
 * @fls: the filedescriptor to write to
 * Return: number of characters printed
 */
int _dec(int num, int fls)
{
	int (*__putchar)(char) = _putchar;
	int z, count = 0;
	unsigned int _abs_, current;

	if (fls == STDERR_FILENO)
		__putchar = _eputchar;
	if (num < 0)
	{
		_abs_ = -num;
		__putchar('-');
		count++;
	}
	else
		_abs_ = num;
	current = _abs_;
	for (z = 1000000000; z > 1; z /= 10)
	{
		if (_abs_ / z)
		{
			__putchar('0' + current / z);
			count++;
		}
		current %= z;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * crt_num - converter function
 * @data: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *crt_num( int data, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = data;

	if (!(flags & CONVERT_UNSIGNED) && data < 0)
	{
		n = -data;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "123abc" : "123ABC";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rmcm - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: Always 0;
 */
void rmcm(char *buf)
{
	int z;

	for (z = 0; buf[z] != '\0'; z++)
		if (buf[z] == '#' && (!z || buf[z - 1] == ' '))
		{
			buf[z] = '\0';
			break;
		}
}

