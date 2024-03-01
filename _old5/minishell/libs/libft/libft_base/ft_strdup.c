/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:52:23 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 09:44:47 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

char	*ft_strdup(const char *str1)
{
	size_t	len;
	char	*str2;

	len = ft_strlen(str1);
	str2 = malloc(sizeof(*str2) * (len + 1));
	if (!str2)
		return (NULL);
	(void) ft_strlcpy(str2, str1, len + 1);
	return (str2);
}
