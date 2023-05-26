#include "shell.h"

/**
 * is_cmd - Determine if token is executabble
 * @info: Info struct
 * @path: Path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	return (st.st_mode & S_IFREG);
}

/**
 * dup_chars - Duplicate characters
 * @pathstr: The PATH string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: Pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i, k;

	for (i = start, k = 0; i < stop; i++)
	{
		if (pathstr[i] != ':')
		{
			buf[k++] = pathstr[i];
		}
	}

	buf[k] = '\0';
	return (buf);
}

/**
 * find_path - Finds the command in the PATH string.
 * @info: The info struct
 * @pathstr: PATH string
 * @cmd: Command to find
 *
 * Return: Full path of the command if found, or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	for (i = 0; ; i++)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);

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

			curr_pos = i;
		}
	}

	return (NULL);
}
