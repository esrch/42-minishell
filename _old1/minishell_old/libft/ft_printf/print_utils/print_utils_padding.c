/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_padding.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:51:02 by erabbath          #+#    #+#             */
/*   Updated: 2023/07/12 07:35:44 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_internal.h"

static void	print_padding(size_t char_count, t_padding padding,
		t_specifier *specifier, int *len)
{
	if (specifier->min_width <= (int) char_count)
		return ;
	if (padding == PADDING_ZERO)
		print_zeros(specifier->min_width - char_count, len);
	else
		print_spaces(specifier->min_width - char_count, len);
}

void	print_left_padding(size_t char_count, t_padding padding,
		t_specifier *specifier, int *len)
{
	if (*len < 0)
		return ;
	if (specifier->alignment == ALIGN_RIGHT)
		print_padding(char_count, padding, specifier, len);
}

void	print_right_padding(size_t char_count, t_padding padding,
		t_specifier *specifier, int *len)
{
	if (*len < 0)
		return ;
	if (specifier->alignment == ALIGN_LEFT)
		print_padding(char_count, padding, specifier, len);
}

void	print_precision_padding(size_t digit_count, t_specifier *specifier,
		int *len)
{
	if (*len < 0)
		return ;
	if (specifier->precision > (ssize_t)digit_count)
		print_zeros((size_t)specifier->precision - digit_count, len);
}
