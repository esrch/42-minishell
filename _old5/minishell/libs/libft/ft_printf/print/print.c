/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:51:02 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 12:17:16 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_internal.h"

void	print_special(t_specifier *specifier, va_list args, int *len)
{
	if (specifier->conversion == CONVERT_PERCENT)
		print_c('%', specifier, len);
	else if (specifier->conversion == CONVERT_CHAR)
		print_c(va_arg(args, int), specifier, len);
	else if (specifier->conversion == CONVERT_STRING)
		print_s(va_arg(args, char *), specifier, len);
	else if (specifier->conversion == CONVERT_INT)
		print_d(va_arg(args, int), specifier, len);
	else if (specifier->conversion == CONVERT_UNSIGNED_INT)
		print_u(va_arg(args, unsigned int), specifier, len);
	else if (specifier->conversion == CONVERT_HEX_LOWER
		|| specifier->conversion == CONVERT_HEX_UPPER)
		print_x(va_arg(args, unsigned int), specifier, len);
	else if (specifier->conversion == CONVERT_POINTER)
		print_p(va_arg(args, unsigned long), specifier, len);
}
