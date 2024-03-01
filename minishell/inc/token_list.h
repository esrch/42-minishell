#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include <stdlib.h>

# include "token.h"

typedef struct s_token_list
{
	struct s_token_list	*next;
	t_token				*token;
}	t_token_list;

int				token_list_add(t_token_list **list, t_token *token);
int				token_list_add_op(t_token_list **list, t_token_type type);
int				token_list_add_word(t_token_list **list, char *value);
void			token_list_destroy(t_token_list *list);
size_t			token_list_len(t_token_list *list);
t_token_list	*token_list_at(t_token_list *list, size_t index);

#endif