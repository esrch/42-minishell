#include "ast.h"

#include "libft.h"
#include "word_list.h"

static void	print_margin(int margin)
{
	ft_printf("%*s", margin * 4, " ");
}

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

static void	print_subshell(t_ast_node *node, int margin)
{
	ft_printf("Subshell:\n");
	margin++;
	print_margin(margin);
	ft_printf("Content: ");
	ast_print(node->left, margin);
}

static void	print_cmd(t_ast_node *node)
{
	int			i;
	t_word_list	*argv_list;

	i = 0;
	ft_printf("Command:");
	argv_list = node->cmd_argv_list;
	while (argv_list)
	{
		ft_printf(" %s", argv_list->word);
		i++;
		argv_list = argv_list->next;
	}
	ft_printf("\n");
}

void	ast_print(t_ast_node *ast, int margin)
{
	if (!ast)
		return ;
	else if (ast->type == AST_CMD)
		print_cmd(ast);
	else if (ast->type == AST_SUBSHELL)
		print_subshell(ast, margin);
	else
		print_binary(ast, margin);
}