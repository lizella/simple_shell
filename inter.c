#include "shell.h"
/**
 * inter - interactive mode
 * @passinfo: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int inter(info_t *passinfo)
{
	return (isatty(STDIN_FILENO) && passinfo->readfd <= 2);
}

/**
 * check1 - checks if character delimeter
 * @ch: the char to check
 * @str: the string
 * Return: 1 if true, 0 if false
 */
int check1(char ch, char *str)
{
	while (*str)
		if (*str++ == ch)
			return (1);
	return (0);
}

/**
 * check2 - checks for alphabetic character
 * @num: The character
 * Return: 1 if num is alphabetic, 0 otherwise
 */

int check2(int num)
{
	if ((num >= 'a' && num <= 'z'))
		return (1);
	else
		return (0);
}

/**
 * check3 - string to integer
 * @data: the string
 * Return: 0 if no numbers in string, converted number otherwise
 */

int check3(char *data)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; data[i] != '\0' && flag != 2; i++)
	{
		if (data[i] == '-')
			sign *= -1;

		if (data[i] >= '0' && data[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (data[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

