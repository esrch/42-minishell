/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:51:02 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 12:17:16 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_internal.h"

void	print_c(unsigned char c, t_specifier *specifier, int *len)
{
	print_left_padding(1, PADDING_SPACE, specifier, len);
	ft_write_count(1, &c, 1, len);
	print_right_padding(1, PADDING_SPACE, specifier, len);
}

static size_t	count_chars_s(char *str, t_specifier *specifier)
{
	if (specifier->precision >= 0)
		return (ft_strlen_max(str, specifier->precision));
	return (ft_strlen(str));
}

void	print_s(char *str, t_specifier *specifier, int *len)
{
	size_t	char_count;

	if (!str)
		str = "(null)";
	char_count = count_chars_s(str, specifier);
	print_left_padding(char_count, PADDING_SPACE, specifier, len);
	if (char_count > 0)
		ft_write_count(1, str, char_count, len);
	print_right_padding(char_count, PADDING_SPACE, specifier, len);
}
