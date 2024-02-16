#include "ft_sprintf_malloc.h"

#include <stdarg.h>
#include <stdlib.h>

#include "libft.h"

static int	get_len(char *format, va_list args)
{
	int		len;
	va_list	args_cpy;

	len = 0;
	va_copy(args_cpy, args);
	while (*format)
	{
		if (*format == '%' && format[1] == '%')
		{
			len++;
			format += 2;
		}
		else if (*format == '%' && format[1] == 'c')
		{
			(void) va_arg(args_cpy, int);
			len++;
			format += 2;
		}
		else if (*format == '%' && format[1] == 's')
		{
			len += ft_strlen(va_arg(args_cpy, char *));
			format += 2;
		}
		else
		{
			len++;
			format++;
		}
	}
	va_end(args_cpy);
	return (len);
}

static void	fill_string(char *result, char *format, va_list args)
{
	char	*s;

	while (*format)
	{
		if (*format == '%' && format[1] == '%')
		{
			*result++ = '%';
			format += 2;
		}
		else if (*format == '%' && format[1] == 'c')
		{
			*result++ = va_arg(args, int);
			format += 2;
		}
		else if (*format == '%' && format[1] == 's')
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

char	*ft_sprintf_malloc(char *format, ...)
{
	char	*result;
	va_list	args;
	int		len;

	va_start(args, format);
	len = get_len(format, args);
	result = malloc(sizeof(*result) * (len + 1));
	if (!result)
		return (NULL);
	fill_string(result, format, args);
	va_end(args);
	return (result);
}
