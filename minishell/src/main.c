#include <unistd.h>

#include "libft.h"
#include "ast.h"
#include "exec.h"
#include "ft_error.h"
#include "global.h"
#include "parser.h"
#include "token_list.h"
#include "tokenizer.h"
#include "heredoc.h"

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	char			cmd[1024];
	int				bytes;
	t_token_list	*token_list;
	t_ast_node		*ast;
	int				exit_status;

	global_set_program_name(argv[0]);

	// TODO: Setup signals

	// Read command line
	bytes = read(STDIN_FILENO, cmd, 1024);
	if (bytes < 0)
	{
		error_print_system();
		return (2);
	}
	cmd[bytes - 1] = '\0';

	// Tokenize command line
	token_list = tokenize(cmd);
	if (!token_list)
		return (2);
	token_list_print(token_list);

	// Parse command into AST
	ast = parse(token_list);
	token_list_clear(token_list);
	if (!ast)
		return (2);
	global_set_ast(ast);
	ast_print(ast, 0);

	// TODO: Init all heredocs
	heredoc_init(ast);

	// TODO: Execute AST
	exit_status = exec_ast(ast);

	// Cleanup
	global_clean();

	return (exit_status);
}