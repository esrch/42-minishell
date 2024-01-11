#include "_minishell.h"

/** Initialize error type and message
 * 
 * Required before using has_error
*/
void	error_init(t_error *error)
{
	error->type = ERR_NONE;
	error->msg = NULL;
}

/** Sets system error
 * 
*/
void	error_set_system(t_error *error)
{
	error->type = ERR_SYSTEM;
}

/** Sets custom error
 * 
 * msg must be a non-NULL string that can be freed
*/
void	error_set_custom(t_error *error, char *msg)
{
	error->type = ERR_CUSTOM;
	error->msg = msg;
}

/** Frees the error message and resets all fieds to defaults
 * 
*/
void	error_cleanup(t_error *error)
{
	free(error->msg);
	error_init(error);
}

/** Prints error with optional prompt
 * 
 * Does nothing if no error.
 * If system error, prints system error (using perror).
 * If custom error, prints custom message.
 * If prompt is not NULL, error message is preceded with "<prompt>: ".
*/
void	error_print(t_error *error, char *prompt)
{
	if (error->type == ERR_NONE)
		return ;
	if (error->type == ERR_SYSTEM)
	{
		perror(prompt);
		return ;
	}
	if (prompt)
	{
		ft_putstr_fd(prompt, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error->msg, 2);
	ft_putstr_fd("\n", 2);
}

/** Checks if there is an error
 * 
 * Returns true if error is NULL or set to anything else than ERR_NONE
*/
bool	has_error(t_error *error)
{
	return (!error || error->type != ERR_NONE);
}