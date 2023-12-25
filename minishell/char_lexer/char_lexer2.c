#include "char_lexer.h"

bool	char_lexer_is_at_end(t_char_lexer *lexer)
{
	return (char_lexer_peek(lexer) == 0);
}

char	char_lexer_advance(t_char_lexer *lexer)
{
	return (lexer->src[lexer->current++]);
}

static int	find(char *haystack, char needle)
{
	int	i;

	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle)
			return (i);
		i++;
	}
	return (-1);
}

int	char_lexer_advance_delim(t_char_lexer *lexer, char *delim)
{
	char	c;
	int		count;

	count = 0;
	c = char_lexer_peek(lexer);
	while (!char_lexer_is_at_end(lexer) && find(delim, c) < 0)
	{
		count++;
		char_lexer_advance(lexer);
		c = char_lexer_peek(lexer);
	}
	return (count);
}

int	char_lexer_advance_while(t_char_lexer *lexer, bool (*predicate)(char c))
{
	int	count;

	count = 0;
	while (predicate(char_lexer_peek(lexer)))
	{
		count++;
		char_lexer_advance(lexer);
	}
	return (count);
}
