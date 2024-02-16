#include "ft_error.h"

#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "libft.h"

void	error_init(t_error *error)
{
	error->type = ERR_NONE;
	error->msg = NULL;
}

void	error_cleanup(t_error *error)
{
	free(error->msg);
	error_init(error);
}

void	error_set_system(t_error *error)
{
	error_cleanup(error);
	error->type = ERR_SYSTEM;
}

void	error_set_custom(t_error *error, char *msg)
{
	error_cleanup(error);
	if (!msg)
		error_set_system(error);
	else
	{
		error->type = ERR_CUSTOM;
		error->msg = msg;
	}
}

void	error_print(t_error *error)
{
	if (error->type == ERR_NONE)
		return ;
	else if (error->type == ERR_SYSTEM)
		perror(global_get_prog_name());
	else
	{
		ft_putstr_fd(global_get_prog_name(), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(error->msg, STDERR_FILENO);
	}
}

void	error_print_custom(char *msg)
{
	t_error	error;

	error_init(&error);
	error_set_custom(&error, msg);
	error_print(&error);
	error_cleanup(&error);
}

void	error_print_system(void)
{
	t_error	error;

	error_init(&error);
	error_set_system(&error);
	error_print(&error);
}

bool	has_error(t_error *error)
{
	return (error->type != ERR_NONE);
}
