/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:50:32 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 09:44:47 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	if (!s1 && !s2)
		return (s1);
	if (n == 0)
		return (s1);
	if (s2 > s1)
		return (ft_memcpy(s1, s2, n));
	while (--n)
		((unsigned char *) s1)[n] = ((unsigned char *) s2)[n];
	((unsigned char *) s1)[n] = ((unsigned char *) s2)[n];
	return (s1);
}
