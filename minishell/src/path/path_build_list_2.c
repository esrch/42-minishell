#include "path.h"
#include "path_build_list_internal.h"

#include "ft_error.h"
#include "ft_sprintf.h"
#include "libft.h"
#include "scanner.h"

/** Frees the paths and full_path if needed, and returns NULL.
 * 
*/
static t_word_list	*handle_error(t_word_list *paths, char *full_path)
{
	if (paths)
		word_list_destroy(paths);
	if (full_path)
		free(full_path);
	return (NULL);
}

/** Builds a full path from a prefix and a filename.
 * 
 * Adds a slash at the end of the prefix if required.
 * 
 * Returns the full path, or NULL on error.
*/
char	*build_full_path(char *prefix, char *filename, t_error *error)
{
	char	*full_path;

	if (prefix[ft_strlen(prefix) - 1] == '/')
		full_path = ft_sprintf("%s%s", prefix, filename);
	else
		full_path = ft_sprintf("%s/%s", prefix, filename);
	if (full_path)
		return (full_path);
	ft_error_set_system(error);
	return (NULL);
}

/** Returns the current directory if it has not been added yet, otherwise NULL.
 * 
 * Updates added_current to true.
*/
char	*add_current_dir(t_scanner *scanner, char *filename,
	bool *added_current, t_error *error)
{
	char	*path;

	if (*added_current)
	{
		scanner_advance_while(scanner, ":");
		scanner_skip(scanner);
		return (NULL);
	}
	path = build_full_path("./", filename, error);
	if (!path)
		return (NULL);
	*added_current = true;
	scanner_advance_while(scanner, ":");
	scanner_skip(scanner);
	return (path);
}

/** Returns the next full path in the scanner.
 * 
*/
char	*next_full_path(t_scanner *scanner, char *filename,
	bool *added_current, t_error *error)
{
	char	*prefix;
	char	*full_path;

	if (scanner_check(scanner, ':'))
		return (add_current_dir(scanner, filename, added_current, error));
	scanner_advance_until(scanner, ":");
	prefix = scanner_extract(scanner);
	if (!prefix)
	{
		ft_error_set_system(error);
		return (NULL);
	}
	full_path = build_full_path(prefix, filename, error);
	free(prefix);
	if (ft_has_error(error))
		return (NULL);
	if (scanner_check(scanner, ':') && scanner_peek_next(scanner) == '\0')
		return (full_path);
	scanner_match(scanner, ":");
	scanner_skip(scanner);
	return (full_path);
}

/** Handles the case when there is no slash in the filename.
 * 
 * env_path is the environment path in the standard format "path1:path2:...".
 * 
 * Returns the path list, which can be NULL if env_path is empty or NULL.
*/
t_word_list	*path_build_list_no_slash(char *env_path, char *filename,
	t_error *error)
{
	t_word_list	*paths;
	t_scanner	*scanner;
	char		*full_path;
	bool		added_current;

	paths = NULL;
	added_current = false;
	scanner = scanner_create(env_path);
	if (!scanner)
	{
		ft_error_set_system(error);
		return (NULL);
	}
	while (!scanner_is_at_end(scanner))
	{
		full_path = next_full_path(scanner, filename, &added_current, error);
		if (ft_has_error(error))
			return (handle_error(paths, NULL));
		if (full_path && word_list_add(&paths, full_path) != 0)
			return (handle_error(paths, full_path));
		free(full_path);
	}
	scanner_destroy(scanner);
	return (paths);
}
