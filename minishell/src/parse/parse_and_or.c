#include "parse.h"
#include "parse_internal.h"

#include <stdlib.h>

/** Creates a new parent and/or node with an existing node as left,
 * and a new node as right.
 * 
 * Returns the new node, or NULL on error.
*/
static t_ast_node	*extend_and_or(t_tl_scanner *scanner, t_ast_node *left,
	t_error *error)
{
	t_ast_node	*node;
	t_ast_type	type;
	t_ast_node	*right;

	if (tl_scanner_check_type(scanner, T_AND))
		type = AST_AND;
	else
		type = AST_OR;
	(void) tl_scanner_advance(scanner);
	right = parse_pipeline(scanner, error);
	if (has_error(error))
		return (NULL);
	node = ast_create_binary(type, left, right);
	if (!node)
	{
		error_set_system(error);
		ast_destroy(right);
	}
	return (node);
}

/** Parses an and/or node.
 * 
 * Returns the new node, or NULL on error.
*/
t_ast_node	*parse_and_or(t_tl_scanner *scanner, t_error *error)
{
	t_ast_node	*node;
	t_ast_node	*tmp_node;

	node = parse_pipeline(scanner, error);
	if (has_error(error))
		return (NULL);
	while (tl_scanner_check_type(scanner, T_AND)
		|| tl_scanner_check_type(scanner, T_OR))
	{
		tmp_node = extend_and_or(scanner, node, error);
		if (has_error(error))
		{
			ast_destroy(node);
			return (NULL);
		}
		node = tmp_node;
	}
	return (node);
}
