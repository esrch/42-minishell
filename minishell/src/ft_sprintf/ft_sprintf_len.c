#include "ft_sprintf.h"
#include "ft_sprintf_internal.h"

#include <stdarg.h>

#include "libft.h"

/** Handles special formats starting with %.
 * 
 * format should point to the character after the %.
 * len is a pointer to the length that will be updated.
 * args is the current state of the var args.
 * 
 * Returns the new format position
*/
static char	*handle_special(char *format, int *len, va_list args)
{
	if (*format == '%')
	{
		*len += 1;
		return (format + 1);
	}
	if (*format == 'c')
	{
		*len += 1;
		(void) va_arg(args, char);
		return (format + 1);
	}
	if (*format == 's')
	{
		*len += ft_strlen(va_arg(args, char *));
		return (format + 1);
	}
	*len += 1;
	return (format);
}

/** Returns the length of the string to be created by sprintf
 * 
*/
int	ft_sprintf_len(char *format, va_list args)
{
	int		len;
	va_list	args_cpy;

	len = 0;
	va_copy(args_cpy, args);
	while (*format)
	{
		if (format[0] == '%')
			format = handle_special(format + 1, &len, args_cpy);
		else
		{
			len++;
			format++;
		}
	}
	va_end(args_cpy);
	return (len);
}