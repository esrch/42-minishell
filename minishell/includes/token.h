#ifndef TOKEN_H
# define TOKEN_H

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

// Token.
void	token_init(t_token *token, t_token_type token_type, char *lexeme,
			char *value);
t_token	*token_construct(t_token_type token_type, char *lexeme,
			char *value);
void	token_cleanup(t_token *token);
void	token_destruct(t_token *token);

// Token utils.
t_token	*token_word(char *lexeme, char *value);
t_token	*token_op(t_token_type token_type);
char	*token_tostring(t_token *token);

#endif /* TOKEN_H */