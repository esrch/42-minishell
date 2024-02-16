#include "ast.h"

#include <stdlib.h>

#include "ft_error.h"
#include "redirection.h"
#include "word_list.h"

t_ast_node	*ast_create_binary(t_ast_type type, t_ast_node *left,
	t_ast_node *right, t_error *error)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node)
	{
		new_node->type = type;
		new_node->left = left;
		new_node->right = right;
		new_node->cmd_argv_list = NULL;
		new_node->cmd_redir = NULL;
		new_node->cmd_argv = NULL;
	}
	else
		error_set_system(error);
	return (new_node);
}

t_ast_node	*ast_create_subshell(t_ast_node *left, t_error *error)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node)
	{
		new_node->type = AST_SUBSHELL;
		new_node->left = left;
		new_node->right = NULL;
		new_node->cmd_argv_list = NULL;
		new_node->cmd_redir = NULL;
		new_node->cmd_argv = NULL;
	}
	else
		error_set_system(error);
	return (new_node);
}

t_ast_node	*ast_create_cmd(t_word_list *argv, t_redir_list *redir, t_error *error)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node)
	{
		new_node->type = AST_CMD;
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->cmd_argv_list = argv;
		new_node->cmd_redir = redir;
		new_node->cmd_argv = NULL;
	}
	else
		error_set_system(error);
	return (new_node);
}

void	ast_destroy(t_ast_node *ast)
{
	int	i;

	if (!ast)
		return ;
	word_list_destroy(ast->cmd_argv_list);
	redir_list_destroy(ast->cmd_redir);
	ast_destroy(ast->left);
	ast_destroy(ast->right);
	if (ast->cmd_argv)
	{
		i = 0;
		while (ast->cmd_argv[i])
		{
			free(ast->cmd_argv[i]);
			i++;
		}
		free(ast->cmd_argv);
	}
	free(ast);
}

void	ast_foreach(t_ast_node *ast, void (*f)(t_ast_node *node, void *arg), void *arg)
{
	if (!ast)
		return ;
	ast_foreach(ast->left, f, arg);
	f(ast, arg);
	ast_foreach(ast->right, f, arg);
}