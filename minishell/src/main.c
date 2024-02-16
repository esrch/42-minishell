#include <readline/readline.h>
#include <stdlib.h>

#include "ast.h"
#include "env.h"
#include "exec.h"
#include "ft_error.h"
#include "global.h"
#include "libft.h"
#include "parse.h"
#include "redirection.h"
#include "token_list.h"
#include "tokenize.h"

static void	read_heredoc(t_ast_node *node, void *arg)
{
	(void) arg;
	heredoc_read(node->redirections);
}

int main(int argc, char **argv, char **envp)
{
	char			*cmd;
	t_error			error;
	t_token_list	*token_list;
	t_ast_node		*ast;

	(void) argc;
	error_init(&error);
	global_init_prog_name(argv[0]);
	if (env_init(envp) != 0)
	{
		error_print_system(NULL);
		exit(1);
	}
	cmd = readline("> ");
	token_list = tokenize(cmd, &error);
	free(cmd);
	if (has_error(&error))
	{
		error_print(&error);
		error_clear(&error);
		exit(1);
	}
	ast = parse(token_list, &error);
	token_list_destroy(token_list);
	if (has_error(&error))
	{
		error_print(&error);
		error_clear(&error);
		exit(1);
	}
	ast_foreach(ast, read_heredoc, NULL);
	exec_ast(ast);
	ast_destroy(ast);
}