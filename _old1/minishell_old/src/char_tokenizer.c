#include "../includes/minishell.h"

void	char_tokenizer_init(t_char_tokenizer *tokenizer, char *src)
{
	tokenizer->src = src;
	tokenizer->start = 0;
	tokenizer->current = 0;
}

t_char_tokenizer	*char_tokenizer_construct(char *src)
{
	t_char_tokenizer	*tokenizer;

	tokenizer = malloc(sizeof(t_char_tokenizer));
	if (!tokenizer)
		return (NULL);
	char_tokenizer_init(tokenizer, src);
	return (tokenizer);
}

void	char_tokenizer_destruct(t_char_tokenizer *tokenizer)
{
	free(tokenizer);
}

char	*char_tokenizer_extract(t_char_tokenizer *tokenizer)
{
	int		i;
	int		len;
	char	*extracted;

	len = tokenizer->current - tokenizer->start;
	extracted = malloc(sizeof(char) * (len + 1));
	if (!extracted)
		return (NULL);
	i = 0;
	while (i < len)
	{
		extracted[i] = tokenizer->src[tokenizer->start + i];
		i++;
	}
	extracted[i] = 0;
	tokenizer->start = tokenizer->current;
	return (extracted);
}