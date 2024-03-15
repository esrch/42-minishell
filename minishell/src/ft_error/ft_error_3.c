#include "ft_error.h"
#include "ft_error_internal.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

/** Prints the error according to the error type with the given prefixes.
 * 
 * If no error is set, nothing is printed.
 * In case of a system error, the system error is printed.
 * In case of a custom error, the custom error message is printed
 * if set, otherwise prints "Error".
*/
void	ft_error_print(char *prefix1, char *prefix2, t_error *error)
{
	if (error->type == ERR_NONE)
		return ;
	if (error->type == ERR_SYSTEM)
		ft_error_print_system(prefix1, prefix2);
	else
		ft_error_print_custom(prefix1, prefix2, error->msg);
}

/** Prints a system error with the given prefixes.
 * 
*/
void	ft_error_print_system(char *prefix1, char *prefix2)
{
	if (prefix1)
	{
		ft_putstr_fd(prefix1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (prefix2)
	{
		ft_putstr_fd(prefix2, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	perror(NULL);
}

/** Prints a custom error with the given prefixes.
 * 
 * Prints the custom error message if it is set,
 * otherwise it prints "Error".
*/
void	ft_error_print_custom(char *prefix1, char *prefix2, char *msg)
{
	if (prefix1)
	{
		ft_putstr_fd(prefix1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (prefix2)
	{
		ft_putstr_fd(prefix2, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	else
		ft_putendl_fd("Error", STDERR_FILENO);
}