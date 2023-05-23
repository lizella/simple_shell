#include "shell.h"
/**
 * his_fl - gets the history file
 * @info: struct
 * Return: allocated string containg history file
 */

char *his_fl(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * w_his - creates a file, or appends to an existing file
 * @info: struct
 * Return: 1 on success, else -1
 */
int w_his(info_t *info)
{
	ssize_t fls;
	char *filename = his_fl(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fls = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fls == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfls(node->str, fls);
		_putfd('\n', fls);
	}
	_putfd(BUF_FLUSH, fls);
	close(fls);
	return (1);
}

/**
 * rd_hist - reads history from file
 * @info: struct
 * Return: histcount on success, 0 otherwise
 */
int rd_hist(info_t *info)
{
	int z, b = 0, count = 0;
	ssize_t fls, readlen, filesize = 0;
	struct stat st;
	char *buf = NULL, *filename = his_fl(info);

	if (!filename)
		return (0);

	fls = open(filename, O_RDONLY);
	free(filename);
	if (fls == -1)
		return (0);
	if (!fstat(fls, &st))
		filesize = st.st_size;
	if (filesize < 2)
		return (0);
	buf = malloc(sizeof(char) * (filesize + 1));
	if (!buf)
		return (0);
	readlen = read(fls, buf, filesize);
	buf[filesize] = 0;
	if (readlen <= 0)
		return (free(buf), 0);
	close(fls);
	for (z = 0; z < filesize; z++)
		if (buf[z] == '\n')
		{
			buf[z] = 0;
			hist_lst(info, buf + b, count++);
			b = z + 1;
		}
	if (b != i)
		hist_lst(info, buf + b, count++);
	free(buf);
	info->histcount = count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * hist_lst - adds entry to a history linked list
 * @info: Struct
 * @b: buffer
 * @count: the history linecount, histcount
 *
 * Return: Always 0
 */
int hist_lst (info_t *info, char *buf, int count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber - renumbers the history linked list after changes
 * @info: Struct
 * Return: the new histcount
 */
int renumber(info_t *info)
{
	list_t *node = info->history;
	int z = 0;

	while (node)
	{
		node->num = z++;
		node = node->next;
	}
	return (info->histcount = z);
}
