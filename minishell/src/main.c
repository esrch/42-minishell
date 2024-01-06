#include "_minishell.h"

int	main(int argc, char **argv)
{
	char			*cmd_line;
	t_token_list	*token_list;
	t_error			error;
	t_token_list	*current;

	(void) argc;
	// TODO: Setup signal handling
	cmd_line = readline("> ");
	while (cmd_line && *cmd_line)
	{
		token_list = ms_tokenize(cmd_line, &error);
		if (has_error(&error))
			error_print(&error, argv[0]);
		else
		{
			current = token_list;
			while (current)
			{
				printf("%d\n", current->token->type);
				current = current->next;
			}
		}
		token_list_clear(&token_list);
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