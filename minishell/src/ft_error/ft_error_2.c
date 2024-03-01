#include "ft_error.h"
#include "ft_error_internal.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

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

/** Returns the error message.
 * 
 * Returns the error message, or NULL if it is not set.
*/
char	*ft_error_get_msg(t_error *error)
{
	return (error->msg);
}