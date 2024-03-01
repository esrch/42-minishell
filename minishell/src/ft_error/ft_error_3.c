#include "ft_error.h"
#include "ft_error_internal.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

/** Prints the according to the error type.
 * 
 * If no error is set, nothing is printed.
 * In case of a system error, the system error is printed.
 * In case of a custom error, the custom error message is printed
 * if set, otherwise prints "Error".
*/
void	ft_error_print(t_error *error)
{
	if (error->type == ERR_NONE)
		return ;
	if (error->type == ERR_SYSTEM)
		ft_error_print_system();
	else
		ft_error_print_custom(error->msg);
}

/** Prints a system error.
 * 
*/
void	ft_error_print_system(void)
{
	perror(ft_error_prefix(NULL));
}

/** Prints a custom error.
 * 
 * Prints the custom error message if it is set,
 * otherwise it prints "Error".
*/
void	ft_error_print_custom(char *msg)
{
	char	*prefix;

	prefix = ft_error_prefix(NULL);
	if (prefix)
	{
		ft_putstr_fd(prefix, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	else
		ft_putendl_fd("Error", STDERR_FILENO);
}