#include "exec.h"
#include "exec_internal.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "ast.h"

int	exec_ast(t_ast_node *ast)
{
	if (!ast)
		return (0);
	if (ast->type == AST_AND)
		return (exec_and(ast));
	else if (ast->type == AST_OR)
		return (exec_or(ast));
	else if (ast->type == AST_PIPE)
		return (exec_pipeline(ast));
	if (ast->type == AST_SUBSHELL)
		return (exec_simple_subshell(ast));
	if (ast->type == AST_CMD)
		return (exec_simple_cmd(ast));
	printf("Invalid AST node\n");
	return (1);
}