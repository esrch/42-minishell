#include "parse.h"
#include "parse_internal.h"

#include <stdlib.h>

#include "ast.h"
#include "ft_error.h"
#include "heredoc_list.h"
#include "tl_scanner.h"

/** Parse a token list into an AST.
 * 
 * Returns the AST, or NULL on error.
*/
t_ast_node	*parse(t_token_list	*token_list, t_heredoc_list **heredocs,
	t_error *error)
{
	t_ast_node		*ast;
	t_tl_scanner	scanner;

	(void) heredocs;
	if (token_list->token->type == T_EOF)
		return (NULL);
	tl_scanner_init(&scanner, token_list);
	ast = parse_and_or(&scanner, heredocs, error);
	if (ft_has_error(error))
	{
		ast_destroy(ast);
		return (NULL);
	}
	return (ast);
}
