#include "global.h"

#include <stdbool.h>
#include <stdlib.h>

#include "libft.h"

static char	*get_last_word(char *argv0)
{
	char	*last_slash;
	char	*tmp_slash;

	last_slash = ft_strchr(argv0, '/');
	if (!last_slash)
		return (argv0);
	tmp_slash = ft_strchr(last_slash + 1, '/');
	while (tmp_slash)
	{
		last_slash = tmp_slash;
		tmp_slash = ft_strchr(last_slash + 1, '/');
	}
	return (last_slash + 1);
}

char	*prog_name(char *argv0)
{
	static char	*program_name = NULL;

	if (argv0)
		program_name = get_last_word(argv0);
	return (program_name);
}

int	last_exit_status(int status)
{
	static int	_last_exit_status = 0;

	if (status >= 0)
		_last_exit_status = status;
	return (_last_exit_status);
}

/** Tracks whether the current process is a subprocess (value of 1)
 * or not (value of 0).
 * 
 * If new_value is 0 or 1, sets the internal value to 0 or 1.
 * For any other new_value, returns the current value.
 * 
 * Returns the current value.
*/
int	in_subprocess(int new_value)
{
	static bool	_in_subprocess = 0;

	if (new_value == 0)
		_in_subprocess = 0;
	else if (new_value == 1)
		_in_subprocess = 1;
	return (_in_subprocess);
}