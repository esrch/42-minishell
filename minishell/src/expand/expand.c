#include "expand.h"
#include "expand_internal.h"

#include <stdlib.h>

#include "ast.h"

static t_word_list	*expand_argv_params(t_word_list *argv)
{
	t_word_list	*expanded_argv;
	char		*expanded_word;
	t_word_list	*split_word;

	while (argv)
	{
		expanded_word = expand_params(argv->word);
		if (!expanded_word)
		{
			word_list_destroy(expanded_argv);
			return (NULL);
		}
		split_word = split_words(expanded_word);
		free(expanded_word);
		if (!split_word)
		{
			word_list_destroy(expanded_argv);
			return (NULL);
		}
		word_list_append(&expanded_argv, split_word);
		argv = argv->next;
	}
	expanded_argv = NULL;
	return (expanded_argv);
}

static t_word_list	*expand_argv_wildcard(t_word_list *argv)
{
	t_word_list	*expanded_argv;
	t_word_list	*expanded_word;

	while (argv)
	{
		expanded_word = expand_wildcard(argv->word);
		if (!expanded_word)
		{
			word_list_destroy(expanded_argv);
			return (NULL);
		}
		word_list_append(&expanded_argv, expanded_word);
		argv = argv->next;
	}
	expanded_argv = NULL;
	return (expanded_argv);
}

/** Expands a command node's argv.
 * 
 * Implements parameter expansion and wildcard expansion.
 * 
 * Returns the expanded params on success, or NULL on error.
*/
char	**expand_argv(t_ast_node *cmd_node)
{
	char		**result;
	t_word_list	*expanded_params_argv;
	t_word_list	*expanded_wildcard_argv;

	expanded_params_argv = expand_argv_param(cmd_node->cmd_argv);
	if (!expanded_params_argv)
		return (NULL);
	expanded_wildcard_argv = expand_argv_wildcard(expanded_params_argv);
	word_list_destroy(expanded_params_argv);
	if (!expanded_wildcard_argv)
		return (NULL);
	expand_unquote(expanded_wildcard_argv);
	result = word_list_to_arr(expanded_wildcard_argv);
	word_list_destroy(expanded_wildcard_argv);
	return (result);
}
