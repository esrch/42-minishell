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

void	token_print(t_token *token)
{
	if (token->type == T_AND_AND)
		printf("T_AND_AND");
	else if (token->type == T_PIPE_PIPE)
		printf("T_PIPE_PIPE");
	else if (token->type == T_PIPE)
		printf("T_PIPE");
	else if (token->type == T_GREAT)
		printf("T_GREAT");
	else if (token->type == T_GREAT_GREAT)
		printf("T_GREAT_GREAT");
	else if (token->type == T_LESS)
		printf("T_LESS");
	else if (token->type == T_LESS_LESS)
		printf("T_LESS_LESS");
	else if (token->type == T_PAREN_OPEN)
		printf("T_PAREN_OPEN");
	else if (token->type == T_PAREN_CLOSE)
		printf("T_PAREN_CLOSE");
	else if (token->type == T_EOF)
		printf("T_EOF");
	else if (token->type == T_WORD)
		printf("T_WORD(%s)", token->lexeme);
	else
		printf("[Error]");
}