#include "tl_scanner.h"

#include <stdlib.h>

#include "ft_error.h"
#include "token.h"
#include "word_list.h"

t_token	*tl_scanner_advance(t_tl_scanner *scanner)
{
	t_token	*token;

	token = scanner->current_node->token;
	if (!tl_scanner_is_at_end(scanner))
		scanner->current_node = scanner->current_node->next;
	return (token);
}

t_token	*tl_scanner_peek(t_tl_scanner *scanner)
{
	return (scanner->current_node->token);
}

bool	tl_scanner_check_type(t_tl_scanner *scanner, t_token_type type)
{
	return (tl_scanner_peek(scanner)->type == type);
}

bool	tl_scanner_match_type(t_tl_scanner *scanner, t_token_type type)
{
	if (tl_scanner_check_type(scanner, type))
	{
		tl_scanner_advance(scanner);
		return (true);
	}
	return (false);
}

t_word_list	*tl_scanner_extract_words(t_tl_scanner *scanner, t_error *error)
{
	t_token		*token;
	t_word_list	*words;

	words = NULL;
	while (tl_scanner_check_type(scanner, T_WORD))
	{
		token = tl_scanner_advance(scanner);
		if (word_list_add(&words, token->value) != 0)
		{
			ft_error_set_system(error);
			word_list_destroy(words);
			return (NULL);
		}
	}
	return (words);
}
