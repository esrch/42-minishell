#ifndef REDIR_LIST_H
# define REDIR_LIST_H

# include "token.h"

typedef struct s_redir_list
{
	struct s_redir_list	*next;
	t_token_type		type;
	char				*word;
	int					fd;
}	t_redir_list;

int				redir_list_add(t_redir_list **list, t_token_type type,
					char *word);
void			redir_list_destroy(t_redir_list *list);
t_redir_list	*redir_list_last(t_redir_list *list);
void			redir_list_close_all(t_redir_list *list);
t_redir_list	*redir_list_apply(t_redir_list *list);
void			redir_list_read_heredocs(t_redir_list *list);

#endif