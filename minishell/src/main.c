#include <unistd.h>

#include "libft.h"
#include "ft_error.h"

int	main(int argc, char **argv)
{
	(void) argc;

	char	cmd[1024];
	int		bytes;
	t_error	error;

	bytes = read(STDIN_FILENO, cmd, 1024);
	if (bytes < 0)
	{
		error_set_system(&error);
		error_print(&error, argv[0]);
	}
	cmd[bytes] = '\0';
	ft_printf("%s\n", cmd);
}