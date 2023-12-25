/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 06:57:06 by erabbath          #+#    #+#             */
/*   Updated: 2023/11/17 06:57:06 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	err_print_special(char *format, va_list args);
static int	err_print_int(int n);

int	ft_printf_error(char *format, ...)
{
	va_list	args;
	int		output_count;
	int		num_chars;

	output_count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			num_chars = err_print_special(format, args);
		}
		else
			num_chars = write(2, format, 1);
		if (num_chars < 0)
		{
			va_end(args);
			return (num_chars);
		}
		output_count += num_chars;
		format++;
	}
	va_end(args);
	return (output_count);
}

static int	err_print_special(char *format, va_list args)
{
	int		c;
	char	*s;
	int		len;

	if (*format == '%')
		return (write(2, "%", 1));
	if (*format == 'c')
	{
		c = va_arg(args, int);
		return (write(2, &c, 1));
	}
	if (*format == 's')
	{
		s = va_arg(args, char *);
		len = ft_strlen(s);
		return (write(2, s, len));
	}
	if (*format == 'd')
		return (err_print_int(va_arg(args, int)));
	return (write(2, format, 1));
}

static int	err_print_int(int n)
{
	int		digit_count;
	char	buffer[10];

	if (n < 0 && write(2, "-", 1) < 0)
		return (-1);
	if (n == 0)
		return (write(1, "0", 1));
	if (n > 0)
		n = -n;
	digit_count = 0;
	while (n)
	{
		digit_count++;
		buffer[10 - digit_count] = "0123456789"[-(n % 10)];
		n /= 10;
	}
	return (write(2, &buffer[10 - digit_count], digit_count));
}
