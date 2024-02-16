#include "ft_sprintf_malloc.h"

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"

static int	count_len(char *format, va_list args)
{
	int		len;
	char	*s;
	va_list	args_cpy;

	va_copy(args_cpy, args);
	len = 0;
	while (*format)
	{
		if (*format == '%' && format[1] == 's')
		{
			s = va_arg(args_cpy, char *);
			len += ft_strlen(s);
			format += 2;
		}
		else if (*format == '%' && format[1] == 'c')
		{
			(void) va_arg(args_cpy, int);
			len++;
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

static char	*fill_string(char *format, va_list args, int len)
{
	char	*s;
	char	c;
	char	*result;
	char	*result_cpy;

	result = malloc(sizeof(*result) * (len + 1));
	if (!result)
		return (NULL);
	result_cpy = result;
	while (*format)
	{
		if (*format == '%' && format[1] == 's')
		{
			s = va_arg(args, char *);
			while (*s)
				*result_cpy++ = *s++;
			format += 2;
		}
		else if (*format == '%' && format[1] == 'c')
		{
			c = va_arg(args, int);
			*result_cpy++ = c;
			format += 2;
		}
		else
			*result_cpy++ = *format++;
	}
	*result_cpy = '\0';
	return (result);
}

char	*ft_sprintf_malloc(char *format, ...)
{
	char	*result;
	int		len;
	va_list	args;

	if (!format)
		return (NULL);
	va_start(args, format);
	len = count_len(format, args);
	result = fill_string(format, args, len);
	va_end(args);
	return (result);
}