/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:04:25 by erabbath          #+#    #+#             */
/*   Updated: 2023/11/06 18:08:56 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

void	**ft_lst_to_arr(t_list *lst)
{
	int		i;
	int		len;
	void	**arr;

	len = ft_lstsize(lst);
	arr = malloc(sizeof(*arr) * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (lst)
	{
		arr[i] = lst->content;
		i++;
		lst = lst->next;
	}
	arr[len] = 0;
	return (arr);
}
