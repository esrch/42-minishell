#include "../includes/minishell.h"

bool	char_tokenizer_is_at_end(t_char_tokenizer *tokenizer)
{
	return (char_tokenizer_peek(tokenizer) == 0);
}

char	char_tokenizer_advance(t_char_tokenizer *tokenizer)
{
	return (tokenizer->src[tokenizer->current++]);
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

int	char_tokenizer_advance_delim(t_char_tokenizer *tokenizer, char *delim)
{
	char	c;
	int		count;

	count = 0;
	c = char_tokenizer_peek(tokenizer);
	while (!char_tokenizer_is_at_end(tokenizer) && find(delim, c) < 0)
	{
		count++;
		char_tokenizer_advance(tokenizer);
		c = char_tokenizer_peek(tokenizer);
	}
	return (count);
}

int	char_tokenizer_advance_while(t_char_tokenizer *tokenizer, bool (*predicate)(char c))
{
	int	count;

	count = 0;
	while (predicate(char_tokenizer_peek(tokenizer)))
	{
		count++;
		char_tokenizer_advance(tokenizer);
	}
	return (count);
}
