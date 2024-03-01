#include "ft_error.h"
#include "ft_error_internal.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

/** Creates a new error.
 * 
 * Error code is set to 0.
 * 
 * Returns a new error, or NULL on error.
*/
t_error	*ft_error_create(void)
{
	t_error	*error;

	error = malloc(sizeof(*error));
	if (!error)
		return (NULL);
	error->type = ERR_NONE;
	error->code = 0;
	error->msg = NULL;
	return (error);
}

/** Frees the memory for the error.
 * 
*/
void	ft_error_destroy(t_error *error)
{
	free(error->msg);
	free(error);
}

/** Resets the error.
 * 
 * Resets the code to 0, frees the error message if present.
*/
void	ft_error_reset(t_error *error)
{
	error->type = ERR_NONE;
	error->code = 0;
	free(error->msg);
	error->msg = NULL;
}

/** Sets or gets the error prefix.
 * 
 * If prefix is NULL, returns the error prefix.
 * Otherwise, sets the prefix to the new value,
 * and returns the error prefix.
*/
char	*ft_error_prefix(char *prefix)
{
	static char	*internal_prefix = NULL;

	if (prefix)
		internal_prefix = prefix;
	return (internal_prefix);
}

/** Checks if an error is set.
 * 
*/
bool	ft_has_error(t_error *error)
{
	return (error->type != ERR_NONE);
}

/** Sets the error to a system error.
 * 
 * Resets the error code to 0 and frees the error message.
*/
void	ft_error_set_system(t_error *error)
{
	ft_error_reset(error);
	error->type = ERR_SYSTEM;
}

/** Sets the error to a custom error.
 * 
*/
void	ft_error_set_custom(t_error *error, int code, char *msg)
{
	ft_error_reset(error);
	error->type = ERR_CUSTOM;
	error->code = code;
	error->msg = msg;
}

/** Returns the error code.
 * 
*/
int	ft_error_get_code(t_error *error)
{
	return (error->code);
}

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