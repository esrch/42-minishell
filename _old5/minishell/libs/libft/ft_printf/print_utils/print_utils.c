/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:51:02 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 12:17:16 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_internal.h"

void	ft_write_count(int fd, void *buf, size_t nbyte, int *len)
{
	ssize_t	result;

	if (*len < 0)
		return ;
	result = write(fd, buf, nbyte);
	if (result < 0)
		*len = result;
	else
		*len += result;
}

static void	print_mult_chars(char *c_50x, size_t n, int *len)
{
	if (*len < 0)
		return ;
	while (n > 50)
	{
		ft_write_count(1, c_50x, 50, len);
		if (*len < 0)
			return ;
		n -= 50;
	}
	if (n)
		ft_write_count(1, c_50x, n, len);
}

void	print_spaces(size_t n, int *len)
{
	static char	*spaces = "                                                  ";

	if (*len >= 0)
		print_mult_chars(spaces, n, len);
}

void	print_zeros(size_t n, int *len)
{
	static char	*zeros = "00000000000000000000000000000000000000000000000000";

	if (*len >= 0)
		print_mult_chars(zeros, n, len);
}
