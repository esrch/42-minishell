/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:08:14 by erabbath          #+#    #+#             */
/*   Updated: 2023/10/21 09:44:47 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

t_list	*create_mapped(void *content, void (*del)(void *))
{
	t_list	*result;

	result = ft_lstnew(content);
	if (!result)
	{
		del(content);
		return (NULL);
	}
	return (result);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map_head;
	t_list	*map_current;

	if (!lst)
		return (NULL);
	map_head = create_mapped(f(lst->content), del);
	if (!map_head)
		return (NULL);
	map_current = map_head;
	while (lst->next)
	{
		lst = lst->next;
		map_current->next = create_mapped(f(lst->content), del);
		if (!map_current->next)
		{
			ft_lstclear(&map_head, del);
			return (NULL);
		}
		map_current = map_current->next;
	}
	return (map_head);
}
