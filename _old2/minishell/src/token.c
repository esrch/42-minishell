#include "token.h"

#include <stdlib.h>

static t_token	*token_create(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

t_token	*token_create_word(char *value)
{
	return (token_create(T_WORD, value));
}

t_token	*token_create_op(t_token_type token_type)
{
	return (token_create(token_type, NULL));
}

void	token_destroy(t_token *token)
{
	free(token->value);
	free(token);
}