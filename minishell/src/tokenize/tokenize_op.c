#include "tokenize.h"
#include "tokenize_internal.h"

#include "ft_error.h"
#include "ft_sprintf.h"
#include "scanner.h"
#include "token_list.h"

/** Sets a syntax error due to an unexpected character
 * 
*/
static void	set_syntax_error(t_scanner *scanner, t_error *error)
{
	error_set_custom(error, ft_sprintf(
		"syntax error near unexpected '%c'", scanner_peek(scanner)));
}

/** Adds a token for an operator to the token list
 * 
*/
void	tokenize_op(t_scanner *scanner, t_token_list **token_list,
	t_error *error)
{
	int	result;

	result = 0;
	if (scanner_match(scanner, "&&"))
		result = token_list_add_op(token_list, T_AND);
	else if (scanner_match(scanner, "||"))
		result = token_list_add_op(token_list, T_OR);
	else if (scanner_match(scanner, "|"))
		result = token_list_add_op(token_list, T_PIPE);
	else if (scanner_match(scanner, "<<"))
		result = token_list_add_op(token_list, T_REDIR_HEREDOC);
	else if (scanner_match(scanner, "<"))
		result = token_list_add_op(token_list, T_REDIR_IN);
	else if (scanner_match(scanner, ">>"))
		result = token_list_add_op(token_list, T_REDIR_APPEND);
	else if (scanner_match(scanner, ">"))
		result = token_list_add_op(token_list, T_REDIR_OUT);
	else if (scanner_match(scanner, "("))
		result = token_list_add_op(token_list, T_PAREN_OPEN);
	else if (scanner_match(scanner, ")"))
		result = token_list_add_op(token_list, T_PAREN_CLOSE);
	else
		set_syntax_error(scanner, error);
	if (!has_error(error) && result != 0)
		error_set_system(error);
}
