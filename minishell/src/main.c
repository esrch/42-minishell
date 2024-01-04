#include "_minishell.h"

int	main(void)
{
	char			*cmd_line;
	t_token_list	*token_list;
	t_token_list	*current;

	// TODO: Setup signal handling
	cmd_line = readline("> ");
	while (cmd_line && *cmd_line)
	{
		token_list = ms_tokenize(cmd_line);
		if (!token_list)
			ft_printf_error("Error");
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