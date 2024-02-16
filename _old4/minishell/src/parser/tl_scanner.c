#include "parser_internal.h"

#include <stdbool.h>

#include "token_list.h"

t_token_list	*tl_scanner_advance(t_token_list **token_list)
{
	t_token_list	*token;

	token = *token_list;
	*token_list = (*token_list)->next;
	return (token);
}

t_token_type	tl_scanner_peek_type(t_token_list **token_list)
{
	return ((*token_list)->type);
}

bool	tl_scanner_check_type(t_token_list **token_list, t_token_type type)
{
	return ((*token_list)->type == type);
}

bool	tl_scanner_match_type(t_token_list **token_list, t_token_type type)
{
	if (tl_scanner_check_type(token_list, type))
	{
		tl_scanner_advance(token_list);
		return (true);
	}
	return (false);
}

bool	tl_scanner_is_at_end(t_token_list **token_list)
{
	return (!token_list || !*token_list || (*token_list)->type == T_EOF);
}