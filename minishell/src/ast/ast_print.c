#include "ast.h"

#include "libft.h"
#include "redirection.h"

/** Prints a margin
 * 
 * Prints four spaces for each margin unit
*/
static void	print_margin(int margin)
{
	ft_printf("%*s", margin * 4, " ");
}

/** Prints a binary AST node
 * 
*/
static void	print_binary(t_ast_node *node, int margin)
{
	if (node->type == AST_PIPE)
		ft_printf("Pipe:\n");
	else if (node->type == AST_AND)
		ft_printf("And:\n");
	else
		ft_printf("Or:\n");
	margin++;
	print_margin(margin);
	ft_printf("Left: ");
	ast_print(node->left, margin);
	print_margin(margin);
	ft_printf("Right: ");
	ast_print(node->right, margin);
}

/** Print a subshell node
 * 
*/
static void	print_subshell(t_ast_node *node, int margin)
{
	ft_printf("Subshell:\n");
	margin++;
	print_margin(margin);
	ft_printf("Redirections: ");
	redir_list_print(node->redirections);
	ft_printf("\n");
	print_margin(margin);
	ft_printf("Left: ");
	ast_print(node->left, margin);
}

/** Print a command node
 * 
*/
static void	print_cmd(t_ast_node *node, int margin)
{
	int			i;

	i = 0;
	ft_printf("Command:\n");
	margin++;
	print_margin(margin);
	word_list_print(node->cmd_argv);
	ft_printf("\n");
	print_margin(margin);
	redir_list_print(node->redirections);
	ft_printf("\n");
}

/** Print an AST node
 * 
*/
void	ast_print(t_ast_node *ast, int margin)
{
	if (!ast)
		return ;
	else if (ast->type == AST_CMD)
		print_cmd(ast, margin);
	else if (ast->type == AST_SUBSHELL)
		print_subshell(ast, margin);
	else
		print_binary(ast, margin);
}
