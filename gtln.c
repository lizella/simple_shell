#include "shell.h"
/**
 * ibuf - buffers chained commands
 * @passinfo: struct
 * @b: address of buffer
 * @length: address of len var
 * Return: bytes read
 */
ssize_t ibuf(info_t *passinfo, char **b, size_t *length)
{
	ssize_t x = 0;
	size_t y = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*b);
		*b = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		x = getline(b, &y, stdin);
#else
		x = _getline(passinfo, b, &y);
#endif
		if (x > 0)
		{
			if ((*b)[x - 1] == '\n')
			{
				(*b)[x - 1] = '\0'; /* remove trailing newline */
				x--;
			}
			passinfo->linecount_flag = 1;
			remove_comments(*b);
			build_history_list(passinfo, *b, passinfo->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*length = x;
				info->cmd_buf = b;
			}
		}
	}
	return (x);
}

/**
 * gLine - gets a line minus the newline
 * @passinfo: struct
 * Return: bytes read
 */
ssize_t gLine(info_t *passinfo)
{
	static char *b;
	static size_t z, x, y;
	ssize_t l = 0;
	char **buf_p = &(passinfo->arg), *p;

	_putchar(BUF_FLUSH);
	l = input_buf(passinfo, &b, &y);
	if (l == -1) 
		return (-1);
	if (y)
	{
		x = z;
		p = b + z; 

		check_chain(passinfo, b, &x, z, y);
		while (x < y)
		{
			if (is_chain(passinfo, b, &x))
				break;
			x++;
		}

		z = x + 1;
		if (z >= y) 
		{
			z = y = 0; 
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; 
		return (_strlen(p));
	}

	*buf_p = buf;
	return (l); 
}

/**
 * rdB - reads a buffer
 * @passinfo:  struct
 * @b: buffer
 * @n: size
 * Return: r
 */
ssize_t rdB(info_t *passinfo, char *b, size_t *n)
{
	ssize_t z = 0;

	if (*n)
		return (0);
	z = read(passinfo->readfd, buf, READ_BUF_SIZE);
	if (z >= 0)
		*n = z;
	return (z);
}

/**
 * _gtLn - gets the next line of input from STDIN
 * @passinfo: struct
 * @a: address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _gtLn(info_t *passinfo, char **a, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t z, num;
	size_t x;
	ssize_t y = 0, s = 0;
	char *v = NULL, *pp = NULL, *m;

	v = *a;
	if (v && len)
		s = *len;
	if (z == num)
		z = num = 0;

	y = read_buf(passinfo, buf, &num);
	if (y == -1 || (y == 0 && num == 0))
		return (-1);

	m = _strchr(buf + z, '\n');
	x = m ? 1 + (unsigned int)(c - buf) : num;
	pp = _realloc(v, s, s ? s + x : x + 1);
	if (!pp) 
		return (v ? free(p), -1 : -1);

	if (s)
		_strncat(pp, buf + z, x - z);
	else
		_strncpy(pp, buf + z, x - z + 1);

	s += x - z;
	z = x;
	v = pp;

	if (len)
		*len = s;
	*len = v;
	return (s);
}

/**
 * ctrHndlr - blocks ctrl-C
 * @num: the signal number
 * Return: void
 */
void ctrHndlr(__attribute__((unused))int num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

