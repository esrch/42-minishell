#include "minishell.h"

t_token	*token_word(char *lexeme, char *value)
{
	return (token_construct(T_WORD, lexeme, value));
}

t_token	*token_op(t_token_type token_type)
{
	return (token_construct(token_type, NULL, NULL));
}

char	*token_tostring(t_token *token)
{
	if (token->type == T_AND_AND)
		return ("T_AND_AND");
	else if (token->type == T_PIPE_PIPE)
		return ("T_PIPE_PIPE");
	else if (token->type == T_PIPE)
		return ("T_PIPE");
	else if (token->type == T_GREAT)
		return ("T_GREAT");
	else if (token->type == T_GREAT_GREAT)
		return ("T_GREAT_GREAT");
	else if (token->type == T_LESS)
		return ("T_LESS");
	else if (token->type == T_LESS_LESS)
		return ("T_LESS_LESS");
	else if (token->type == T_PAREN_OPEN)
		return ("T_PAREN_OPEN");
	else if (token->type == T_PAREN_CLOSE)
		return ("T_PAREN_CLOSE");
	else if (token->type == T_EOF)
		return ("T_EOF");
	else if (token->type == T_WORD)
		return ("T_WORD");
	return (NULL);
}
