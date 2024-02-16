#include "path.h"

#include <unistd.h>

#include "ft_error.h"
#include "ft_sprintf_malloc.h"
#include "libft.h"
#include "scanner.h"

static char	*build_path(char *prefix, char *filename, t_error *error)
{
	char	*full_path;

	if (prefix[ft_strlen(prefix) - 1] == '/')
		full_path = ft_sprintf_malloc("%s%s", prefix, filename);
	else
		full_path = ft_sprintf_malloc("%s/%s", prefix, filename);
	if (!full_path)
		error_set_system(error);
	return (full_path);
}

static char	*cwd_prefix(t_scanner *scanner, t_error *error)
{
	char	*prefix;

	prefix = ft_strdup("./");
	if (!prefix)
		error_set_system(error);
	scanner_advance_while(scanner, ":");
	scanner_skip(scanner);
	return (prefix);
}

static char	*next_prefix(t_scanner *scanner, t_error *error)
{
	char	next_char;

	if (scanner_is_at_end(scanner))
		return (NULL);
	next_char = scanner_advance(scanner);
	if (next_char == ':' && scanner_is_at_end(scanner))
		return (cwd_prefix(scanner, error));
	if (next_char == ':' && scanner_check(scanner, ':'))
		return (cwd_prefix(scanner, error));
	scanner_advance_until(scanner, ":");
	return (scanner_extract(scanner, error));
}

static char	*first_prefix(t_scanner *scanner, t_error *error)
{
	if (!scanner_is_at_end(scanner))
		return (NULL);
	if (scanner_check(scanner, ':'))
		return (cwd_prefix(scanner, error));
	else
		return (next_prefix(scanner, error));
}

static void	update_path_info(t_path_info *path_info, char *prefix, char *filename,
	t_error *error)
{
	char	*full_path;

	full_path = build_path(prefix, filename, error);
	if (has_error(error))
		return ;
	if (access(full_path, F_OK) == 0)
	{
		free(path_info->path);
		path_info->path = full_path;
		path_info->is_exec = access(full_path, X_OK) == 0;
	}
	else
		free(full_path);
}

static void	handle_path_search(t_path_info *path_info, char *filename, char *path,
	t_error *error)
{
	t_scanner	scanner;
	char		*prefix;

	if (!path || !*path)
		return ;
	scanner_init(&scanner, path);
	prefix = first_prefix(&scanner, error);
	while (prefix)
	{
		if (!has_error(error))
			update_path_info(path_info, prefix, filename, error);
		free(prefix);
		if (has_error(error))
			return ;
		prefix = next_prefix(&scanner, error);
	}
}

static void	handle_slash_path(t_path_info *path_info, char *filename, t_error *error)
{

	if (access(filename, F_OK) != 0)
		return ;
	path_info->path = ft_strdup(filename);
	if (!path_info->path)
		error_set_system(error);
	else
		path_info->is_exec = access(filename, X_OK) == 0;
}

t_path_info	path_search(char *filename, char *path, t_error *error)
{
	t_path_info	path_info;

	path_info.path = NULL;
	path_info.is_exec = false;
	if (ft_strchr(filename, '/'))
		handle_slash_path(&path_info, filename, error);
	else
		handle_path_search(&path_info, filename, path, error);
	if (has_error(error))
	{
		free(path_info.path);
		path_info.path = NULL;
		path_info.is_exec = false;
	}
	return (path_info);
}