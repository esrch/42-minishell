#include <unistd.h>

#include "libft.h"
#include "ft_error.h"
#include "token_list.h"
#include "tokenizer.h"

int	main(int argc, char **argv)
{
	(void) argc;

	char			cmd[1024];
	int				bytes;
	t_error			error;
	t_token_list	*token_list;

	error_init(&error);
	bytes = read(STDIN_FILENO, cmd, 1024);
	if (bytes < 0)
	{
		error_set_system(&error);
		error_print(&error, argv[0]);
		return (2);
	}
	cmd[bytes - 1] = '\0';
	token_list = tokenize(cmd, &error);
	if (has_error(&error))
	{
		error_print(&error, argv[0]);
		error_cleanup(&error);
		return (2);
	}
	token_list_print(token_list);
	error_cleanup(&error);
	token_list_clear(token_list);
}