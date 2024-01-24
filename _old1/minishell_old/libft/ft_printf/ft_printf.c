/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:51:02 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 12:13:20 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static void	init_specifier(t_specifier *specifier)
{
	specifier->alignment = ALIGN_RIGHT;
	specifier->sign = SIGN_DEFAULT;
	specifier->is_alternative = 0;
	specifier->padding = PADDING_SPACE;
	specifier->min_width = 0;
	specifier->precision = -1;
	specifier->format_len = 0;
}

static size_t	handle_normal(char *format, int *len)
{
	size_t	i;

	i = 1;
	while (format[i] && format[i] != '%')
		i++;
	ft_write_count(1, format, i, len);
	return (i);
}

static size_t	handle_special(char *format, va_list args, int *len)
{
	t_specifier	specifier;

	init_specifier(&specifier);
	parse_specifier(format, args, &specifier);
	if (specifier.conversion == CONVERT_INVALID)
		ft_write_count(1, format, 1, len);
	else
		print_special(&specifier, args, len);
	return (specifier.format_len);
}

static int	ft_printf_core(char *format, va_list args)
{
	int	len;

	len = 0;
	while (*format)
	{
		if (*format == '%')
			format += handle_special(format, args, &len);
		else
			format += handle_normal(format, &len);
		if (len < 0)
			return (len);
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		result;
	va_list	args;

	va_start(args, format);
	result = ft_printf_core((char *)format, args);
	va_end(args);
	return (result);
}
