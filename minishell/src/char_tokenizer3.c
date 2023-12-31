#include "../includes/minishell.h"

char	char_tokenizer_previous(t_char_tokenizer *tokenizer)
{
	return (tokenizer->src[tokenizer->current - 1]);
}

char	char_tokenizer_peek(t_char_tokenizer *tokenizer)
{
	return (tokenizer->src[tokenizer->current]);
}

bool	char_tokenizer_match(t_char_tokenizer *tokenizer, char *expected)
{
	int	i;

	i = 0;
	while (expected[i]
		&& tokenizer->src[tokenizer->current + i]
		&& expected[i] == tokenizer->src[tokenizer->current + i])
		i++;
	if (expected[i] != 0)
		return (false);
	tokenizer->current += i;
	return (true);
}
