#include "exec_internal.h"

#include <stdbool.h>
#include "ast.h"

int	exec_group(t_ast_node *node, bool is_top_level)
{
	if (node->left->type == AST_AND)
		return (exec_and(node->left));
	else if (node->left->type == AST_OR)
		return (exec_or(node->left));
	else if (node->left->type == AST_GROUP)
		return (exec_group(node->left, is_top_level));
	else if (node->left->type == AST_PIPE)
		return (exec_pipeline(node->left));
	else
		return (exec_single_cmd(node->left));
}