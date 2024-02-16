#include "../../inc/expansion.h"
#include "expansion_internal.h"

#include <stdlib.h>
#include "../../inc/env.h"
#include "../../inc/error.h"
#include "../../inc/token_list.h"
#include "../../inc/word_list.h"

static void	expand_word(t_token_list **node, t_env env, t_error *error)
{
	char		*expanded;
	t_word_list	*word_list;

	expanded = expand_params((*node)->token->value, env, error);
	if (has_error(error))
		return ;
	word_list = split_words(expanded, " \t\n", error);
	free(expanded);
	if (has_error(error))
		return ;
	// Expand wildcard
	// Split words
	// Replace new token list
}

void	expand_words(t_token_list **token_list, t_env env, t_error *error)
{
	t_token_list	**current;

	current = token_list;
	while (*current)
	{
		if ((*current)->token->type == T_WORD)
			expand_word(current, env, error);
		current = &(*current)->next;
	}
}