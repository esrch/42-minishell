#ifndef PATH_H
# define PATH_H

# include <stdbool.h>

# include "ft_error.h"

typedef struct s_path_info
{
	char	*path;
	bool	is_exec;
}	t_path_info;

t_path_info	path_search(char *filename, char *path, t_error *error);

#endif