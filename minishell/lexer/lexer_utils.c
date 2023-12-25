#include "lexer.h"

bool	lexer_is_at_end(t_lexer *lexer)
{
	return (lexer->source[lexer->current] == 0);
}

char	lexer_advance(t_lexer *lexer)
{
	return (lexer->source[lexer->current++]);
}

char	lexer_peek(t_lexer *lexer)
{
	return (lexer->source[lexer->current]);
}

bool	lexer_match(t_lexer *lexer, char expected)
{
	if (lexer_is_at_end(lexer))
		return (false);
	if (lexer_peek(lexer) != expected)
		return (false);
	lexer->current++;
	return (true);
}
