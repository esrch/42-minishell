#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include "defines.h"
# include "token.h"

typedef struct s_token_list
{
	struct s_token_list	*prev;
	struct s_token_list	*next;
	t_token				*token;
}	t_token_list;

t_status	token_list_add_op(t_token_list **list, t_token_type type);
t_status	token_list_add_word(t_token_list **list, char *value);
void		token_list_clear(t_token_list *list);
void		token_list_print(t_token_list *list);

#endif /* TOKEN_LIST_H */