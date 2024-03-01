#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>

typedef enum e_token_type
{
	T_WORD,
	T_AND,
	T_OR,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_HEREDOC,
	T_REDIR_APPEND,
	T_PAREN_OPEN,
	T_PAREN_CLOSE,
	T_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

t_token	*token_create_op(t_token_type type);
t_token	*token_create_word(char *value);
void	token_destroy(t_token *token);
bool	token_is_redirection_type(t_token_type type);
void	token_print(t_token *token);

#endif