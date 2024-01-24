#include "tl_scanner.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ft_error.h"
#include "token.h"
#include "token_list.h"
#include "word_list.h"

void	tl_scanner_init(t_tl_scanner *scanner, t_token_list *list)
{
	scanner->start = list;
	scanner->current = list;
}

t_token_type	tl_scanner_peek_type(t_tl_scanner *scanner)
{
	return (scanner->current->token->type);
}

t_token	*tl_scanner_advance(t_tl_scanner *scanner)
{
	t_token	*token;

	if (tl_scanner_is_at_end(scanner))
		return (NULL);
	token = scanner->current->token;
	scanner->current =scanner->current->next;
	return (token);
}

void	tl_scanner_advance_while(t_tl_scanner *scanner, t_token_type type)
{
	while (!tl_scanner_is_at_end(scanner) && scanner->current->token->type == type)
		scanner->current = scanner->current->next;
}

bool	tl_scanner_match_type(t_tl_scanner *scanner, t_token_type type)
{
	if (tl_scanner_peek_type(scanner) != type)
		return (false);
	tl_scanner_advance(scanner);
	return (true);
}

bool	tl_scanner_is_at_end(t_tl_scanner *scanner)
{
	return (tl_scanner_peek_type(scanner) == T_EOF);
}

void	tl_scanner_sync_start(t_tl_scanner *scanner)
{
	scanner->start = scanner->current;
}


t_word_list	*tl_scanner_extract_values(t_tl_scanner *scanner, t_error *error)
{
	char		*word_cpy;
	t_word_list	*values;

	values = NULL;
	while (scanner->start != scanner->current)
	{
		// Remove dependency on <string.h>
		word_cpy = strdup(scanner->start->token->value);
		if (!word_cpy)
			error_set_system(error);
		else
			word_list_add(&values, word_cpy, error);
		if (has_error(error))
		{
			free(word_cpy);
			word_list_clear(values);
			return (NULL);
		}
		scanner->start = scanner->start->next;
	}
	return (values);
}
