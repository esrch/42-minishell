#include "../includes/minishell.h"

int	main(void)
{
	char			*line;

	// TODO: Setup signal handling
	line = readline("> ");
	while (line && *line)
	{
		// TODO: Tokenize
		// TODO: Expand parameters
		// TODO: Split words
		// TODO: Expand file names
		// TODO: Split words
		// TODO: Parse into AST
		// TODO: Execute AST
		free(line);
		line = readline("> ");
	}
	free(line);
}