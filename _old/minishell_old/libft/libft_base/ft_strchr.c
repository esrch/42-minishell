/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:52:18 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 09:44:47 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c2;

	i = 0;
	c2 = (char) c;
	while (s[i] && s[i] != c2)
		i++;
	if (s[i] == c2)
		return ((char *) s + i);
	return (NULL);
}
