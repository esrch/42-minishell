#include "../includes/minishell.h"

int	cond_add_file(t_list **file_list, char *filename, char *pattern)
{
	char	*filename_cpy;
	t_list	*new_elem;

	if (*filename == '.' && *pattern != '.')
		return (0);
	if (wildcard_match(pattern, filename))
	{
		filename_cpy = ft_strdup(filename);
		if (!filename)
			return (-1);
		new_elem = ft_lstnew((void *)filename_cpy);
		if (!new_elem)
		{
			free(filename_cpy);
			return (-1);
		}
		ft_lstadd_back(file_list, new_elem);
	}
	return (0);
}

void	free_file(void *filename)
{
	free(filename);
}

t_list	*build_file_list(char *pattern)
{
	char			pwd[4096];
	DIR				*dir;
	struct dirent	*dirent;
	t_list			*file_list;
	
	file_list = NULL;
	getcwd(pwd, 4096);
	dir = opendir(pwd);
	dirent = readdir(dir);
	while (dirent)
	{
		if (cond_add_file(&file_list, dirent->d_name, pattern) < 0)
		{
			ft_lstclear(&file_list, free_file);
			return (NULL);
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (file_list);
}