#include "minishell.h"

int	main(void)
{
	char	*cmd;

	cmd = readline("> ");
	printf("%s.\n", cmd);
	free(cmd);
}