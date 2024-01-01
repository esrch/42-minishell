#include "_minishell.h"

int	main(void)
{
	char	*cmd_line;

	// TODO: Setup signal handling
	cmd_line = readline("> ");
	while (cmd_line && *cmd_line)
	{
		// TODO: Tokenize command line
		// TODO: Parameter expansion
		// TODO: Split words
		// TODO: Filename expansion
		// TODO: Split words
		// TODO: Parse tokens to AST
		// TODO: Execute AST
		ft_printf("Your commande: %s\n", cmd_line);
		free(cmd_line);
		cmd_line = readline("> ");
	}
}