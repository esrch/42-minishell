#include "ft_sprintf.h"
#include "ft_sprintf_internal.h"

#include <stdarg.h>

/** Fills s with the required content
 * 
*/
void	ft_sprintf_fill(char *format, va_list args, char *result)
{
	char	*s;

	while (*format)
	{
		if (format[0] == '%' && format[1] == '%')
		{
			*result++ = '%';
			format += 2;
		}
		else if (format[0] == '%' && format[1] == 'c')
		{
			*result++ = va_arg(args, int);
			format += 2;
		}
		else if (format[0] == '%' && format[1] == 's')
		{
			s = va_arg(args, char *);
			while (*s)
				*result++ = *s++;
			format += 2;
		}
		else
			*result++ = *format++;
	}
	*result = '\0';
}