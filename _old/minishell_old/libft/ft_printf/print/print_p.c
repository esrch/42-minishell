/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:51:02 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 12:17:16 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_internal.h"

static size_t	count_chars(unsigned long value, size_t digit_count,
	t_specifier *specifier)
{
	size_t	char_count;

	if (value == 0)
		return (3);
	char_count = digit_count + 2;
	if (specifier->precision > (ssize_t)digit_count)
		char_count = specifier->precision + 2;
	if (specifier->sign != SIGN_DEFAULT)
		char_count++;
	return (char_count);
}

static void	print_prefixes(t_specifier *spec, int *len)
{
	print_sign(1, spec->sign, len);
	print_hex_prefix(spec->conversion == CONVERT_HEX_UPPER, len);
}

static void	print_value(unsigned long value, size_t digit_count,
	t_specifier *spec, int *len)
{
	uprint_hex_digits(value, digit_count,
		spec->conversion == CONVERT_HEX_UPPER, len);
}

void	print_p(unsigned long value, t_specifier *spec, int *len)
{
	size_t			digit_count;
	size_t			char_count;

	digit_count = ucount_digits(value, 16, spec->precision);
	char_count = count_chars(value, digit_count, spec);
	if (spec->padding == PADDING_ZERO)
		print_prefixes(spec, len);
	print_left_padding(char_count, spec->padding, spec, len);
	if (spec->padding == PADDING_SPACE)
		print_prefixes(spec, len);
	print_precision_padding(digit_count, spec, len);
	print_value(value, digit_count, spec, len);
	print_right_padding(char_count, spec->padding, spec, len);
}
