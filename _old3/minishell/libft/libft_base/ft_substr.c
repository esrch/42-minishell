/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:53:26 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 09:44:47 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

static char	*empty_str(void)
{
	char	*str;

	str = malloc(sizeof(char));
	if (str)
		str[0] = 0;
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	real_len;
	char	*str;

	real_len = 0;
	while (real_len < start + len && s[real_len])
		real_len++;
	if (real_len <= start)
		return (empty_str());
	real_len = real_len - start;
	str = malloc(sizeof(char) * (real_len + 1));
	if (!str)
		return (NULL);
	(void) ft_strlcpy(str, s + start, real_len + 1);
	return (str);
}
