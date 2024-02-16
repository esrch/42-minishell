#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include <stdbool.h>

# include "ft_error.h"

typedef enum e_token_type
{
	T_WORD,
	T_AND,
	T_OR,
	T_PAREN_OPEN,
	T_PAREN_CLOSE,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_HEREDOC,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_EOF
}	t_token_type;

typedef struct s_token_list
{
	struct s_token_list	*next;
	t_token_type		type;
	char				*value;
}	t_token_list;

void	token_list_add(t_token_list **list, t_token_type type, char *value, t_error *error);
void	token_list_add_op(t_token_list **list, t_token_type type, t_error *error);
void	token_list_destroy(t_token_list *list);
bool	token_list_is_redir(t_token_list *node);
bool	token_list_is_and_or(t_token_list *node);
void	token_list_print(t_token_list *list);

#endif