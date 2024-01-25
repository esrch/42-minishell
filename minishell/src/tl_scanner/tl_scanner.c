#include "tl_scanner.h"

#include <stdbool.h>
#include "token.h"
#include "token_list.h"

t_token	*tl_scanner_advance(t_token_list **token_list)
{
	t_token	*token;

	token = (*token_list)->token;
	*token_list = (*token_list)->next;
	return (token);
}

t_token	*tl_scanner_peek(t_token_list **token_list)
{
	return ((*token_list)->token);
}

t_token_type	tl_scanner_peek_type(t_token_list **token_list)
{
	return ((*token_list)->token->type);
}

bool	tl_scanner_check_type(t_token_list **token_list, t_token_type type)
{
	return (tl_scanner_peek_type(token_list) == type);
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
	return (!token_list || !*token_list || (*token_list)->token->type == T_EOF);
}