#include "exec_internal.h"

#include "ast.h"

/** Executes the subnode of an AND or */
static int	exec_subnode(t_ast_node *node)
{
	if (node->type == AST_AND)
		return (exec_and(node));
	else if (node->type == AST_OR)
		return (exec_or(node));
	else if (node->type == AST_PIPE)
		return (exec_pipeline(node));
	else if (node->type == AST_SUBSHELL)
		return (exec_simple_subshell(node));
	else
		return (exec_simple_cmd(node));
	return (1);
}

/** Executes an AND AST node.
 * 
 * Returns the exit code of the left branch if the exit code is not 0.
 * Otherwise, returns the exit code of the right branch.
*/
int	exec_and(t_ast_node *node)
{
	int	left_result;

	left_result = exec_subnode(node->left);
	if (left_result == 0)
		return (exec_subnode(node->right));
	else
		return (left_result);
}

/** Executes an OR AST node.
 * 
 * Returns the exit code of the left branch if the exit code is 0.
 * Otherwise, returns the exit code of the right branch.
*/
int exec_or(t_ast_node *node)
{
	int	left_result;

	left_result = exec_subnode(node->left);
	if (left_result != 0)
		return (exec_subnode(node->right));
	else
		return (left_result);
}