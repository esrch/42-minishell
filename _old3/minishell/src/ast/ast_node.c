#include "ast.h"

#include <stdlib.h>
#include "redirection_list.h"
#include "word_list.h"
#include "ft_error.h"

t_ast_node	*ast_node_create_binary(t_ast_node_type type, t_ast_node *left,
	t_ast_node *right)
{
	t_ast_node	*node;

	node = malloc(sizeof(*node));
	if (node)
	{
		node->type = type;
		node->left = left;
		node->right = right;
		node->cmd_argv = NULL;
		node->cmd_redirections = NULL;
	}
	else
		error_print_system();
	return (node);
}

t_ast_node	*ast_node_create_group(t_ast_node *left)
{
	t_ast_node	*node;

	node = malloc(sizeof(*node));
	if (node)
	{
		node->type = AST_GROUP;
		node->left = left;
		node->right = NULL;
		node->cmd_argv = NULL;
		node->cmd_redirections = NULL;
	}
	else
		error_print_system();
	return (node);
}

t_ast_node	*ast_node_create_cmd(t_word_list *argv, t_redirection_list *redirections)
{
	t_ast_node	*node;
	
	node = malloc(sizeof(*node));
	if (node)
	{
		node->type = AST_CMD;
		node->left = NULL;
		node->right = NULL;
		node->cmd_argv = argv;
		node->cmd_redirections = redirections;
	}
	else
		error_print_system();
	return (node);
}

void	ast_node_destroy(t_ast_node *ast)
{
	if (!ast)
		return ;
	ast_node_destroy(ast->right);
	ast_node_destroy(ast->left);
	word_list_clear(ast->cmd_argv);
	redirection_list_clear(ast->cmd_redirections);
	free(ast);
}