#include "_minishell.h"

void	token_init(t_token *token, t_token_type type, char *value)
{
	token->type = type;
	token->value = value;
}

void	token_init_word(t_token *token, char *value)
{
	token_init(token, T_WORD, value);
}

void	token_init_op(t_token *token, t_token_type token_type)
{
	token_init(token, token_type, NULL);
}

void	token_cleanup(t_token *token)
{
	free(token->value);
}