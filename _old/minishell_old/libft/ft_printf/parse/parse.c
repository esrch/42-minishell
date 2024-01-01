/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:51:02 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 12:17:16 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_internal.h"

static int	parse_flags(char *format, t_specifier *specifier)
{
	int	i;

	i = 0;
	while (format[i] == '-' || format[i] == '+' || format[i] == '#'
		|| format[i] == ' ' || format[i] == '0')
	{
		if (format[i] == '-')
		{
			specifier->alignment = ALIGN_LEFT;
			specifier->padding = PADDING_SPACE;
		}
		else if (format[i] == '+')
			specifier->sign = SIGN_PLUS;
		else if (format[i] == ' ' && specifier->sign != SIGN_PLUS)
			specifier->sign = SIGN_SPACE;
		else if (format[i] == '#')
			specifier->is_alternative = 1;
		else if (format[i] == '0' && specifier->alignment != ALIGN_LEFT)
			specifier->padding = PADDING_ZERO;
		i++;
	}
	return (i);
}

static int	parse_min_width(char *format, va_list args, t_specifier *specifier)
{
	int	i;

	i = 0;
	if (format[i] == '*')
	{
		specifier->min_width = va_arg(args, int);
		return (1);
	}
	specifier->min_width = 0;
	while (format[i] >= '0' && format[i] <= '9')
	{
		specifier->min_width = specifier->min_width * 10 + (format[i] - '0');
		i++;
	}
	return (i);
}

static int	parse_precision(char *format, va_list args, t_specifier *specifier)
{
	int	i;
	int	precision;

	i = 0;
	if (format[i] != '.')
		return (i);
	i++;
	if (format[i] == '*')
	{
		precision = va_arg(args, int);
		if (precision < 0)
			return (++i);
		specifier->padding = PADDING_SPACE;
		specifier->precision = precision;
		return (++i);
	}
	specifier->padding = PADDING_SPACE;
	specifier->precision = 0;
	while (format[i] >= '0' && format[i] <= '9')
	{
		specifier->precision = specifier->precision * 10 + (format[i] - '0');
		i++;
	}
	return (i);
}

static int	parse_conversion(char *format, t_specifier *specifier)
{
	if (*format == 'c')
		specifier->conversion = CONVERT_CHAR;
	else if (*format == 's')
		specifier->conversion = CONVERT_STRING;
	else if (*format == 'p')
		specifier->conversion = CONVERT_POINTER;
	else if (*format == 'd' || *format == 'i')
		specifier->conversion = CONVERT_INT;
	else if (*format == 'u')
		specifier->conversion = CONVERT_UNSIGNED_INT;
	else if (*format == 'x')
		specifier->conversion = CONVERT_HEX_LOWER;
	else if (*format == 'X')
		specifier->conversion = CONVERT_HEX_UPPER;
	else if (*format == '%')
		specifier->conversion = CONVERT_PERCENT;
	else
	{
		specifier->conversion = CONVERT_INVALID;
		specifier->format_len = 1;
		return (0);
	}
	return (1);
}

void	parse_specifier(char *format, va_list args, t_specifier *specifier)
{
	specifier->format_len = 1;
	specifier->format_len += parse_flags(format + specifier->format_len,
			specifier);
	specifier->format_len += parse_min_width(format + specifier->format_len,
			args, specifier);
	specifier->format_len += parse_precision(format + specifier->format_len,
			args, specifier);
	specifier->format_len += parse_conversion(format + specifier->format_len,
			specifier);
}
