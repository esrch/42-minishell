/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:18:14 by erabbath          #+#    #+#             */
/*   Updated: 2023/11/06 18:20:17 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

t_list	*ft_lstnew_back(t_list **lst, void *content)
{
	t_list	*elem;

	elem = ft_lstnew(content);
	if (!elem)
		return (NULL);
	ft_lstadd_back(lst, elem);
	return (elem);
}
