#include "tokenize.h"
#include "tokenize_internal.h"

#include <stdlib.h>

#include "ft_error.h"
#include "ft_sprintf.h"
#include "scanner.h"

/** Sets a syntax error, and returns NULL.
 * 
*/
static t_token	*syntax_error(t_scanner *scanner, t_error *error)
{
	char	*error_msg;

	error_msg = ft_sprintf("syntax error near unexpected '%c'", scanner_peek(scanner));
	if (!error_msg)
		ft_error_set_system(error);
	else
		ft_error_set_custom(error, 0, error_msg);
	return (NULL);
}

/** Returns the next operator token in the scanner.
 * 
 * Returns the token, or NULL on error.
*/
t_token	*next_op_token(t_scanner *scanner, t_error *error)
{
	t_token	*token;

	if (scanner_match(scanner, "&&"))
		token = token_create_op(T_AND);
	else if (scanner_match(scanner, "||"))
		token = token_create_op(T_OR);
	else if (scanner_match(scanner, "|"))
		token = token_create_op(T_PIPE);
	else if (scanner_match(scanner, "<<"))
		token = token_create_op(T_REDIR_HEREDOC);
	else if (scanner_match(scanner, "<"))
		token = token_create_op(T_REDIR_IN);
	else if (scanner_match(scanner, ">>"))
		token = token_create_op(T_REDIR_APPEND);
	else if (scanner_match(scanner, ">"))
		token = token_create_op(T_REDIR_OUT);
	else if (scanner_match(scanner, "("))
		token = token_create_op(T_PAREN_OPEN);
	else if (scanner_match(scanner, ")"))
		token = token_create_op(T_PAREN_CLOSE);
	else
		return (syntax_error(scanner, error));
	if (!token)
		ft_error_set_system(error);
	return (token);
}
