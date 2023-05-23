#include "shell.h"

/**
 * is_cmd - Determine if a file is an executable command
 * @info: Info struct
 * @path: Path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	if (!path || stat(path, &st) != 0)
		return (0);

	return (S_ISREG(st.st_mode));
}

/**
 * duplic_chars - Duplicate characters
 * @pathstr: PATH string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: Pointer to new buffer
 */
char *duplic_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i, k = 0;

	for (i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	}
	buf[k] = '\0';
	return (buf);
}

/**
 * find_path - Find command in the PATH string
 * @info: Info struct
 * @pathstr: PATH string
 * @cmd: cmd to find
 *
 * Return: Full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplic_chars(pathstr, pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			pos = i;
		}
		i++;
	}

	return (NULL);
}
