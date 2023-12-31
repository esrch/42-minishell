#include "minishell.h"

void	token_init(t_token *token, t_token_type token_type, char *lexeme,
	char *value)
{
	token->type = token_type;
	token->lexeme = lexeme;
	token->value = value;
}

t_token	*token_construct(t_token_type token_type, char *lexeme, char *value)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
		return (NULL);
	token_init(token, token_type, lexeme, value);
	return (token);
}

void	token_cleanup(t_token *token)
{
	free(token->lexeme);
	free(token->value);
}

void	token_destruct(t_token *token)
{
	token_cleanup(token);
	free(token);
}
