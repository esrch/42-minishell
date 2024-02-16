#include "ft_error.h"

#include <stdio.h>

#include "global.h"
#include "libft.h"

/** Prints a system error with the program name as a prompt,
 * as well as an optional prefix.
*/
void	error_print_system(char *prefix)
{
	char	*prog_name;

	prog_name = global_prog_name_get();
	if (!prefix)
		perror(prog_name);
	else
	{
		ft_putstr_fd(prog_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(prefix);
	}
}

/** Prints a custom error with the program name as a prompt
 * 
*/
void	error_print_custom(char *msg)
{
	ft_putstr_fd(global_prog_name_get(), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

/** Prints the error to standard error based on its type
 * 
*/
void	error_print(t_error *error)
{
	if (error->type == E_SYSTEM)
		error_print_system(NULL);
	else if (error->type == E_CUSTOM)
		error_print_custom(error->msg);
}
