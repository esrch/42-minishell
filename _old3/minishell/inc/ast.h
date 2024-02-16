#ifndef AST_H
# define AST_H

# include "redirection_list.h"
# include "word_list.h"

typedef enum e_ast_node_type
{
	AST_AND,
	AST_OR,
	AST_PIPE,
	AST_GROUP,
	AST_CMD
}	t_ast_node_type;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_word_list			*cmd_argv;
	t_redirection_list	*cmd_redirections;
}	t_ast_node;

t_ast_node	*ast_node_create_binary(t_ast_node_type type, t_ast_node *left,
				t_ast_node *right);
t_ast_node	*ast_node_create_group(t_ast_node *left);
t_ast_node	*ast_node_create_cmd(t_word_list *argv, t_redirection_list *redirections);
void		ast_node_destroy(t_ast_node *ast);
void		ast_print(t_ast_node *ast, int margin);

#endif /* AST_NODE_H */