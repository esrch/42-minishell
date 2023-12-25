#include "char_lexer.h"

char	char_lexer_previous(t_char_lexer *lexer)
{
	return (lexer->src[lexer->current - 1]);
}

char	char_lexer_peek(t_char_lexer *lexer)
{
	return (lexer->src[lexer->current]);
}

bool	char_lexer_match(t_char_lexer *lexer, char *expected)
{
	int	i;

	i = 0;
	while (expected[i]
		&& lexer->src[lexer->current + i]
		&& expected[i] == lexer->src[lexer->current + i])
		i++;
	if (expected[i] != 0)
		return (false);
	lexer->current += i;
	return (true);
}
