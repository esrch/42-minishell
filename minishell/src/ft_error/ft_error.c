#include "ft_error.h"

#include <stdbool.h>
#include <stdlib.h>

/** Initializes error to no error.
 * 
*/
void	error_init(t_error *error)
{
	error->type = E_NONE;
	error->msg = NULL;
}

/** Checks whether there is an error
 * 
*/
bool	has_error(t_error *error)
{
	return (error->type != E_NONE);
}

/** Sets the error as a system error.
 * 
*/
void	error_set_system(t_error *error)
{
	error_clear(error);
	error->type = E_SYSTEM;
}

/** Sets the error as a custom error with a custom message.
 * 
 * If msg is NULL, sets the error as a system error
 * (assumes an allocation error).
*/
void	error_set_custom(t_error *error, char *msg)
{
	free(error->msg);
	if (!msg)
		error_set_system(error);
	else
	{
		error->type = E_CUSTOM;
		error->msg = msg;
	}
}

/** Clears the error and frees any allocated memory
 * 
*/
void	error_clear(t_error *error)
{
	free(error->msg);
	error_init(error);
}
