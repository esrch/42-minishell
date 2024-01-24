#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include "token.h"
# include "ft_error.h"

typedef struct s_token_list
{
	struct s_token_list	*prev;
	struct s_token_list	*next;
	t_token				*token;
}	t_token_list;

void	token_list_add_op(t_token_list **list, t_token_type type, t_error *error);
void	token_list_add_word(t_token_list **list, char *value, t_error *error);
void	token_list_clear(t_token_list *list);
void	token_list_print(t_token_list *list);

#endif /* TOKEN_LIST_H */