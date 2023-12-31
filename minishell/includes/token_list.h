#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include "token.h"

typedef struct s_token_list
{
	t_token				*token;
	struct s_token_list	*next;
}	t_token_list;

// Token list.
int				token_list_add(t_token_list **token_list, t_token *token);
t_token_list	*token_list_last(t_token_list *token_list);
int				token_list_add_token_type(t_token_list **token_list,
					t_token_type token_type);
int				token_list_add_word(t_token_list **token_list, char *lexeme,
					char *value);
void			token_list_clear(t_token_list **token_list);
void			token_list_print(t_token_list *token_list);

#endif /* TOKEN_LIST_H */