#include <readline/readline.h>

#include "ast.h"
#include "env.h"
#include "exec.h"
#include "ft_error.h"
#include "heredoc_list.h"
#include "libft.h"
#include "parse.h"
#include "global.h"
#include "token_list.h"
#include "tokenize.h"

static int	handle_init_error(void)
{
	ft_error_print_system(prog_name(NULL), NULL);
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	char			*line;
	t_error			*error;
	t_token_list	*tokens;
	t_ast_node		*ast;
	t_heredoc_list	*heredocs;
	int				heredoc_result;

	(void) argc;
	(void) argv;
	prog_name(argv[0]);
	if (env_init(envp) != 0)
		return (handle_init_error());
	error = ft_error_create();
	if (!error)
		return (handle_init_error());
	while (1)
	{
		line = readline("minishell> ");
		tokens = tokenize(line, error);
		free(line);
		if (ft_has_error(error))
		{
			ft_error_print(prog_name(NULL), NULL, error);
			ft_error_reset(error);
			continue ;
		}
		heredocs = NULL;
		ast = parse(tokens, &heredocs, error);
		token_list_destroy(tokens);
		if (ft_has_error(error))
		{
			ft_error_print(prog_name(NULL), NULL, error);
			ft_error_reset(error);
			heredoc_list_destroy(heredocs);
			continue ;
		}
		heredoc_result = heredoc_list_read(heredocs);
		heredoc_list_destroy(heredocs);
		if (heredoc_result != 0)
		{
			ast_destroy(ast);
			if (heredoc_result == -1)
				ft_error_print_system(prog_name(NULL), NULL);
			continue ;
		}
		exec_ast(ast);
		ast_destroy(ast);
	}
	ft_error_destroy(error);
}