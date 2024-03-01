#ifndef PATH_H
# define PATH_H

# include <stdbool.h>

# include "ft_error.h"
# include "word_list.h"

typedef struct s_path_info
{
	char	*full_path;
	bool	is_exec;
}	t_path_info;

t_word_list	*path_build_list(char *env_path, char *filename, t_error *error);
t_path_info	path_find(t_word_list *paths);

#endif