/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:53:19 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 09:44:47 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

static int	contains(char needle, char const *haystack)
{
	while (*haystack)
	{
		if (*haystack == needle)
			return (1);
		haystack++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	end = ft_strlen(s1);
	if (end == 0)
		return (ft_substr(s1, 0, 0));
	while (--end > 0 && contains(s1[end], set))
		;
	if (end == 0 && contains(s1[end], set))
		return (ft_substr(s1, 0, 0));
	start = 0;
	while (start < end && contains(s1[start], set))
		start++;
	return (ft_substr(s1, start, end - start + 1));
}
