#include "ast.h"

#include <stdlib.h>

#include "redir_list.h"

/** Create a binary AST node with left and right sides.
 * 
 * Returns 0 on success, or -1 on allocation error.
*/
t_ast_node	*ast_create_binary(t_ast_type type, t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->left = left;
	new_node->right = right;
	new_node->redirections = NULL;
	new_node->cmd_argv = NULL;
	return (new_node);
}

/** Creates a subshell AST node.
 * 
 * Returns 0 on success, or -1 on allocation error.
*/
t_ast_node	*ast_create_subshell(t_ast_node *left, t_redir_list	*redirections)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->type = AST_SUBSHELL;
	new_node->left = left;
	new_node->right = NULL;
	new_node->redirections = redirections;
	new_node->cmd_argv = NULL;
	return (new_node);
}

/** Creates a command AST node.
 * 
 * Returns 0 on success, or -1 on allocation error.
*/
t_ast_node	*ast_create_cmd(t_redir_list *redirections, t_word_list *cmd_argv)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->type = AST_CMD;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->redirections = redirections;
	new_node->cmd_argv = cmd_argv;
	return (new_node);
}

/** Frees the memory allocated for the AST
 * 
*/
void	ast_destroy(t_ast_node *ast)
{
	if (!ast)
		return ;
	redir_list_destroy(ast->redirections);
	word_list_destroy(ast->cmd_argv);
	ast_destroy(ast->left);
	ast_destroy(ast->right);
	free(ast);
}

/** Calls the function f on each node of the AST
 * 
*/
void	ast_foreach(t_ast_node *ast, void (*f)(t_ast_node *node, void *arg),
	void *arg)
{
	if (!ast)
		return ;
	ast_foreach(ast->left, f, arg);
	f(ast, arg);
	ast_foreach(ast->right, f, arg);
	
}
