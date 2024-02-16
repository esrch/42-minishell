/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:25:31 by erabbath          #+#    #+#             */
/*   Updated: 2023/11/06 18:48:18 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

void	ft_free_2d_count(void ***arr_ptr, int count)
{
	void	**arr;

	if (!arr_ptr)
		return ;
	arr = *arr_ptr;
	while (count--)
		free(arr[count]);
	free(*arr_ptr);
	*arr_ptr = NULL;
}
