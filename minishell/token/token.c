#include "token.h"

t_token	*token_construct(t_token_type token_type, char *lexeme, char *value)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
		return (NULL);
	token->type = token_type;
	token->lexeme = lexeme;
	token->value = value;
	return (token);
}

void	token_destruct(t_token *token)
{
	free(token->lexeme);
	free(token->value);
	free(token);
}