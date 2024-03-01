/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:04:36 by erabbath          #+#    #+#             */
/*   Updated: 2023/12/05 17:47:44 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

int	ft_max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

long	ft_max_long(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}

float	ft_max_flt(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_max_dbl(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
