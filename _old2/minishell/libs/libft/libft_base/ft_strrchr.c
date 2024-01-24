/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:53:14 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 09:44:47 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	c2;
	char	*result;

	i = 0;
	c2 = (char) c;
	result = NULL;
	while (s[i])
	{
		if (s[i] == c2)
			result = (char *) s + i;
		i++;
	}
	if (s[i] == c2)
		return ((char *) s + i);
	return (result);
}
