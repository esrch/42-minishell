#include "_minishell.h"

void	lexer_init(t_lexer *lexer, char *src)
{
	lexer->src = src;
	lexer->start = 0;
	lexer->current = 0;
}

char	lexer_peek(t_lexer *lexer)
{
	return (lexer->src[lexer->current]);
}

bool	lexer_at_end(t_lexer *lexer)
{
	return (lexer_peek(lexer) == 0);
}

bool	lexer_match(t_lexer *lexer, char c)
{
	if (lexer_peek(lexer) == c)
	{
		(void)lexer_advance(lexer);
		return (true);
	}
	return (false);
}

char	*lexer_extract(t_lexer *lexer)
{
	char	*extracted;

	extracted = ft_substr(lexer->src, lexer->start, lexer->current - lexer->start);
	lexer->start = lexer->current;
	return (extracted);
}