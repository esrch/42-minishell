/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:07:36 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 09:44:47 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

static size_t	count_digits(int n)
{
	size_t	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*zero_string(void)
{
	char	*result;

	result = malloc(sizeof(*result) * 2);
	if (!result)
		return (NULL);
	result[0] = '0';
	result[1] = 0;
	return (result);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*result;

	if (!n)
		return (zero_string());
	len = (n < 0) + count_digits(n);
	result = malloc(sizeof(*result) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = 0;
	if (n < 0)
		result[0] = '-';
	else
		n = -n;
	while (n)
	{
		result[--len] = "0123456789"[-(n % 10)];
		n /= 10;
	}
	return (result);
}
