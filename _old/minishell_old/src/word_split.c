#include "../includes/minishell.h"

static t_token_list	*split_error(char **words,
	t_token_list **token_list, int index)
{

	token_list_clear(token_list);
	while (words[index])
	{
		free(words[index]);
		index++;
	}
	free(words);
	return (NULL);
}

t_token_list	*split_words(t_token *token)
{
	int				i;
	char			**words;
	t_token_list	*token_list;

	words = ft_split(token->value, ' ');
	if (!words)
		return (NULL);
	token_list = NULL;
	i = 0;
	while (words[i])
	{
		if (token_list_add_word(&token_list, NULL, words[i]) < 0)
			return (split_error(words, &token_list, i));
		i++;
	}
	free(words);
	return (token_list);
}