#include "path.h"

#include <unistd.h>

#include "libft.h"

/** Initializes path info.
 * 
*/
static void	path_info_init(t_path_info *path_info)
{
	path_info->full_path = NULL;
	path_info->is_exec = false;
}

/** Updates the path info with the given path.
 * 
*/
static void	update_path_info(char *path, t_path_info *path_info)
{
	if (access(path, F_OK) == 0)
	{
		free(path_info->full_path);
		path_info->full_path = ft_strdup(path);
		path_info->is_exec = access(path, X_OK) == 0;
	}
}

/** Finds the first existing and executable path in paths.
 * 
 * If no path exists, returns the last existing path.
*/
t_path_info	path_find(t_word_list *paths)
{
	t_path_info	path_info;

	path_info_init(&path_info);
	while (paths)
	{
		update_path_info(paths->word, &path_info);
		if (path_info.is_exec)
			return (path_info);
		paths = paths->next;
	}
	return (path_info);
}