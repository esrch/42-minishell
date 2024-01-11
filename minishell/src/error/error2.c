#include "error.h"

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
