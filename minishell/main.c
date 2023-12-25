#include "minishell.h"

int	main(void)
{
	char			*line;
	t_token_list	*token_list;

	line = readline("> ");
	while (line && *line)
	{
		token_list = lexer_scan(line);
		if (token_list)
		{
			token_list_print(token_list);
			token_list_clear(&token_list);
		}
		free(line);
		line = readline("> ");
	}
	free(line);
}