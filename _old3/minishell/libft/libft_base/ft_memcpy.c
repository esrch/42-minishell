/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:20:18 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 09:44:47 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (!s1 && !s2)
		return (s1);
	i = 0;
	while (i < n)
	{
		((unsigned char *) s1)[i] = ((unsigned char *) s2)[i];
		i++;
	}
	return (s1);
}
