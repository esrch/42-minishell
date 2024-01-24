#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>
# include "ft_error.h"

typedef enum e_token_type
{
	T_WORD,
	T_AND_AND,
	T_PIPE,
	T_PIPE_PIPE,
	T_GREAT,
	T_GREAT_GREAT,
	T_LESS,
	T_LESS_LESS,
	T_PAREN_OPEN,
	T_PAREN_CLOSE,
	T_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

t_token	*token_create_op(t_token_type type, t_error *error);
t_token	*token_create_word(char *value, t_error *error);
void	token_destroy(t_token *token);
bool	token_is_redirection(t_token_type type);
bool	token_is_and_or(t_token_type type);
void	token_print(t_token *token);

#endif /* TOKEN_H */