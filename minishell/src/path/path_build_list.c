#include "path.h"
#include "path_build_list_internal.h"

#include "ft_error.h"
#include "ft_sprintf.h"
#include "libft.h"
#include "scanner.h"

/** Handles the case when there is a slash in the filename.
 * 
 * Returns the path list, or NULL on error.
*/
t_word_list	*handle_slash_filename(char *filename, t_error *error)
{
	t_word_list	*paths;

	paths = NULL;
	if (word_list_add(&paths, filename) != 0)
	{
		ft_error_set_system(error);
		return (NULL);
	}
	return (paths);
}

/** Builds a list of full paths.
 * 
 * env_path is the environment path in the standard format "path1:path2:...".
 * 
 * Returns the path list (which can be NULL if env_path is empty or NULL),
 * or NULL on error.
*/
t_word_list	*path_build_list(char *env_path, char *filename, t_error *error)
{
	if (!env_path || !*env_path)
		return (NULL);
	if (ft_strchr(filename, '/'))
		return (handle_slash_filename(filename, error));
	return (path_build_list_no_slash(env_path, filename, error));
}