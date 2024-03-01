#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "token.h"

typedef struct s_redir_list
{
	struct s_redir_list	*next;
	t_token_type		type;
	char				*word;
	int					fd;
}	t_redir_list;

int		redir_list_add(t_redir_list **list, t_token_type type, char	*word);
void	redir_list_destroy(t_redir_list *list);
void	redir_list_print(t_redir_list *list);

int		heredoc_read(t_redir_list *list);

int		redirection_apply(t_redir_list *list);

#endif