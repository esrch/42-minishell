/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:04:36 by erabbath          #+#    #+#             */
/*   Updated: 2023/12/05 17:47:04 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

int	ft_abs_int(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

long	ft_abs_long(long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

float	ft_abs_flt(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}

double	ft_abs_dbl(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}
