#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "ft_error.h"
# include "token_list.h"

typedef struct s_redir_list
{
	struct s_redir_list	*next;
	t_token_type		type;
	char				*file;
	char				*heredoc_term;
	int					heredoc_fd;
}	t_redir_list;

void	redir_list_add(t_redir_list **list, t_token_type type, char *word,
			t_error *error);
void	redir_list_destroy(t_redir_list *list);

#endif