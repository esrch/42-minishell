#include "ft_error.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	error->type = ERR_SYSTEM;
}

void	error_set_custom(t_error *error, char *msg)
{
	error->type = ERR_CUSTOM;
	error->msg = msg;
}

void	error_print(t_error *error, char *prompt)
{
	if (error->type == ERR_NONE)
		return ;
	if (error->type == ERR_SYSTEM)
	{
		perror(prompt);
		return ;
	}
	// Remove dependency on fprintf
	if (prompt)
		fprintf(stderr, "%s: ", prompt);
	fprintf(stderr, "%s\n", error->msg);
}

bool	has_error(t_error *error)
{
	return (error && error->type != ERR_NONE);
}