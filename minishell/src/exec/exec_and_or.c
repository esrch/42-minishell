#include "exec.h"
#include "exec_internal.h"

#include <stdio.h>

static int	exec_subnode(t_ast_node *subnode)
{
	if (subnode->type == AST_AND)
		return (exec_and(subnode));
	if (subnode->type == AST_OR)
		return (exec_or(subnode));
	if (subnode->type == AST_SUBSHELL)
		return (exec_simple_subshell(subnode));
	if (subnode->type == AST_CMD)
		return (exec_simple_cmd(subnode));
	else if (subnode->type == AST_PIPE)
		return (exec_pipeline(subnode));
	return (0);
}

int	exec_and(t_ast_node *and_node)
{
	int	left_result;

	left_result = exec_subnode(and_node->left);
	if (left_result == 0)
		return (exec_subnode(and_node->right));
	return (left_result);
}

int	exec_or(t_ast_node *or_node)
{
	int	left_result;

	left_result = exec_subnode(or_node->left);
	if (left_result != 0)
		return (exec_subnode(or_node->right));
	return (left_result);
}
