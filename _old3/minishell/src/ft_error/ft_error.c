#include "ft_error.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "global.h"

void	error_print_system(void)
{
	perror(global_get_program_name());
}

void	error_print_custom(char *msg)
{
	if (!msg)
		error_print_system();
	else
	{
		ft_putstr_fd(global_get_program_name(), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
		free(msg);
	}
}
