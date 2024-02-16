#include "path.h"
#include "path_internal.h"

#include <unistd.h>

#include "ft_error.h"
#include "ft_sprintf.h"
#include "libft.h"
#include "scanner.h"

/** Builds a path based on a prefix and a filename.
 * 
 * Adds a slash at the end of the prefix if it is missing.
 * Returns the full path, or NULL on error.
*/
static char	*build_path(char *prefix, char *filename)
{
	char	*full_path;

	if (prefix[ft_strlen(prefix) - 1] == '/')
		full_path = ft_sprintf("%s%s", prefix, filename);
	else
		full_path = ft_sprintf("%s/%s", prefix, filename);
	return (full_path);
}

/** Updates the path info after checking if a file exists and is executable.
 * 
 * Returns 0 on success, and -1 on error.
*/
static int	update_path_info(t_path_info *path_info, char *prefix, char *filename)
{
	char	*full_path;

	full_path = build_path(prefix, filename);
	if (!full_path)
		return (-1);
	if (access(full_path, F_OK) == 0)
	{
		free(path_info->path);
		path_info->path = full_path;
		path_info->is_exec = access(full_path, X_OK) == 0;
	}
	else
		free(full_path);
	return (0);
}

/** Handles the case when filename doesn't contain a slash
 * (searches the file in the environment path).
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	handle_path_search(t_path_info *path_info, char *filename, char *path)
{
	t_scanner	scanner;
	char		*prefix;
	bool		is_first;

	if (!path || !*path)
		return (0);
	is_first = true;
	scanner_init(&scanner, path);
	while (!scanner_is_at_end(&scanner))
	{
		prefix = next_prefix(&scanner, is_first);
		is_first = false;
		if (!prefix)
			return (-1);
		if (update_path_info(path_info, prefix, filename) != 0)
		{
			free(prefix);
			return (-1);
		}
		free(prefix);
		if (path_info->path && path_info->is_exec)
			return (0);
	}
	return (0);
}

/** Handles the case when filename contains a slash (no search in the path).
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	handle_slash_path(t_path_info *path_info, char *filename)
{
	if (access(filename, F_OK) != 0)
		return (0);
	path_info->path = ft_strdup(filename);
	if (!path_info->path)
		return (-1);
	path_info->is_exec = access(filename, X_OK) == 0;
	return (0);
}

/** Searches for a file name in the environment path.
 * 
 * If filename contains a slash, the filename is used as is, and is not search
 * on the path.
 * Otherwise, the filename is tested with each component of the path.
 * If an executable file is found in the path, path_info is updated, with the
 * full path stored in path, and is_exec set to true.
 * If no executable file is found, but a non-executable file is found,
 * path_info is updated with the last existing full path stored in path,
 * and is_exec set to false.
 * Otherwise, path_info is updated with path as NULL and is_exec as false.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	path_search(char *filename, char *path, t_path_info *path_info)
{
	int	status;

	path_info->path = NULL;
	path_info->is_exec = false;
	if (ft_strchr(filename, '/'))
		status = handle_slash_path(path_info, filename);
	else
		status = handle_path_search(path_info, filename, path);
	if (status != 0)
	{
		free(path_info->path);
		path_info->path = NULL;
		path_info->is_exec = false;
	}
	return (status);
}