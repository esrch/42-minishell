#include "_minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*cmd_line;
	t_token_list	*token_list;
	t_error			error;

	(void) argc;
	(void) envp;
	error_init(&error);
	// TODO: Setup signal handling
	cmd_line = readline("> ");
	while (cmd_line && *cmd_line)
	{
		token_list = ms_tokenize(cmd_line, &error);
		if (has_error(&error))
			error_print(&error, argv[0]);

		// TODO: Parameter expansion (incl. split words)
		// TODO: Filename expansion (incl. split words)
		// TODO: Parse tokens to AST
		// TODO: Execute AST

		token_list_clear(&token_list);
		free(cmd_line);
		error_cleanup(&error);
		cmd_line = readline("> ");
	}
	free(cmd_line);
}