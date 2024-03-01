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
	if (!error)
		return ;
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
