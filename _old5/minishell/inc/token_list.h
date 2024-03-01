#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include "token.h"

typedef struct s_token_list
{
	struct s_token_list	*next;
	t_token				*token;
}	t_token_list;

int		token_list_add_op(t_token_list **list, t_token_type type);
int		token_list_add_word(t_token_list **list, char *value);
void	token_list_destroy(t_token_list *list);
void	token_list_print(t_token_list *token_list);

#endif