#include "char_lexer.h"

void	char_lexer_init(t_char_lexer *lexer, char *src)
{
	lexer->src = src;
	lexer->start = 0;
	lexer->current = 0;
}

t_char_lexer	*char_lexer_construct(char *src)
{
	t_char_lexer	*lexer;

	lexer = malloc(sizeof(t_char_lexer));
	if (!lexer)
		return (NULL);
	char_lexer_init(lexer, src);
	return (lexer);
}

void	char_lexer_destruct(t_char_lexer *lexer)
{
	free(lexer);
}

char	*char_lexer_extract(t_char_lexer *lexer)
{
	int		i;
	int		len;
	char	*extracted;

	len = lexer->current - lexer->start;
	extracted = malloc(sizeof(char) * (len + 1));
	if (!extracted)
		return (NULL);
	i = 0;
	while (i < len)
	{
		extracted[i] = lexer->src[lexer->start + i];
		i++;
	}
	extracted[i] = 0;
	lexer->start = lexer->current;
	return (extracted);
}