#include "exec_internal.h"

#include "ast.h"

static int	exec_subnode(t_ast_node *node)
{
	if (node->type == AST_AND)
		return (exec_and(node));
	else if (node->type == AST_OR)
		return (exec_or(node));
	else if (node->type == AST_GROUP)
		return (exec_group(node, false));
	else if (node->type == AST_PIPE)
		return (exec_pipeline(node));
	// Attention avec single command vs subcommand
	else
		return (exec_single_cmd(node));
}

int	exec_and(t_ast_node *node)
{
	int	left_result;

	left_result = exec_subnode(node->left);
	if (left_result == 0)
		return (exec_subnode(node->right));
	else
		return (left_result);
}

int exec_or(t_ast_node *node)
{
	int	left_result;

	left_result = exec_subnode(node->left);
	if (left_result != 0)
		return (exec_subnode(node->right));
	else
		return (left_result);
}