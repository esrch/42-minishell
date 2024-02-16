/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:51:02 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 12:17:16 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_internal.h"

void	print_sign(int sign, t_sign sign_char, int *len)
{
	if (*len < 0)
		return ;
	if (sign < 0)
		ft_write_count(1, "-", 1, len);
	else if (sign >= 0 && sign_char == SIGN_PLUS)
		ft_write_count(1, "+", 1, len);
	else if (sign >= 0 && sign_char == SIGN_SPACE)
		ft_write_count(1, " ", 1, len);
}

void	print_hex_prefix(int is_upper, int *len)
{
	if (*len < 0)
		return ;
	if (is_upper)
		ft_write_count(1, "0X", 2, len);
	else
		ft_write_count(1, "0x", 2, len);
}
