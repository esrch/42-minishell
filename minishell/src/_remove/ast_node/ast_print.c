#include "ast_node.h"

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

static void	print_group(t_ast_node *node, int margin)
{
	ft_printf("Group:\n");
	margin++;
	print_margin(margin);
	ft_printf("Content: ");
	ast_print(node->left, margin);
}

static void	print_cmd(t_ast_node *node)
{
	int			i;
	t_word_list	*argv;

	i = 0;
	ft_printf("Command:");
	argv = node->cmd_argv;
	while (argv)
	{
		ft_printf(" %s", argv->word);
		i++;
		argv = argv->next;
	}
	ft_printf("\n");
}

void	ast_print(t_ast_node *ast, int margin)
{
	if (ast->type == AST_CMD)
		print_cmd(ast);
	else if (ast->type == AST_GROUP)
		print_group(ast, margin);
	else
		print_binary(ast, margin);
}