#include "lexer.h"

bool	is_at_end(t_lexer *lexer)
{
	return (lexer->source[lexer->current] == 0);
}

char	advance(t_lexer *lexer)
{
	return (lexer->source[lexer->current++]);
}

char	peek(t_lexer *lexer)
{
	return (lexer->source[lexer->current]);
}

bool	match(t_lexer *lexer, char expected)
{
	if (is_at_end(lexer))
		return (false);
	if (peek(lexer) != expected)
		return (false);
	lexer->current++;
	return (true);
}
