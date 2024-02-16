#ifndef AST_H
# define AST_H

# include "ft_error.h"
# include "redirection.h"
# include "word_list.h"

typedef enum e_ast_type
{
	AST_AND,
	AST_OR,
	AST_PIPE,
	AST_CMD,
	AST_SUBSHELL
}	t_ast_type;

typedef struct s_ast_node
{
	t_ast_type			type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_word_list			*cmd_argv_list;
	t_redir_list		*cmd_redir;
	char				**cmd_argv;
}	t_ast_node;

t_ast_node	*ast_create_binary(t_ast_type type, t_ast_node *left,
				t_ast_node *right, t_error *error);
t_ast_node	*ast_create_subshell(t_ast_node *left, t_error *error);
t_ast_node	*ast_create_cmd(t_word_list *argv, t_redir_list *redir, t_error *error);
void		ast_destroy(t_ast_node *ast);
void		ast_foreach(t_ast_node *ast, void (*f)(t_ast_node *node, void *arg), void *arg);
void		ast_print(t_ast_node *ast, int margin);

#endif