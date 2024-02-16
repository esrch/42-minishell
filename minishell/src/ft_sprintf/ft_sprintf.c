#include "ft_sprintf.h"
#include "ft_sprintf_internal.h"

#include <stdarg.h>
#include <stdlib.h>

/** Returns an allocated string using a format similar to printf.
 * 
 * Implemented special formats: %%, %c, %s.
 * 
 * Returns the allocated string, or NULL on error.
*/
char	*ft_sprintf_malloc(char *format, ...)
{
	char	*result;
	va_list	args;
	int		len;

	va_start(args, format);
	len = ft_sprintf_len(format, args);
	result = malloc(sizeof(*result) * (len + 1));
	if (!result)
		return (NULL);
	ft_sprintf_fill(format, args, result);
	va_end(args);
	return (result);
}
