#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>
# include <stdio.h>

# include "../libft/libft.h"

typedef enum s_token_type
{
	T_WORD,
	T_AND_AND,
	T_PIPE_PIPE,
	T_PIPE,
	T_GREAT,
	T_GREAT_GREAT,
	T_LESS,
	T_LESS_LESS,
	T_PAREN_OPEN,
	T_PAREN_CLOSE,
	T_EOF
}	t_token_type;

typedef struct t_token
{
	t_token_type	type;
	char			*lexeme;
	char			*value;
}	t_token;

typedef struct s_token_list
{
	t_token				*token;
	struct s_token_list	*next;
}	t_token_list;

// Token.
t_token	*token_construct(t_token_type token_type, char *lexeme,
			char *value);
void	token_destruct(t_token *token);
void	token_print(t_token *token);

// Token list.
int		token_list_add(t_token_list **token_list, t_token *token);
int		token_list_add_token_type(t_token_list **token_list,
			t_token_type token_type);
int		token_list_add_word(t_token_list **token_list, char *lexeme,
			char *value);
void	token_list_clear(t_token_list **token_list);
void	token_list_print(t_token_list *token_list);

#endif /* TOKEN_H */