/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:25:31 by erabbath          #+#    #+#             */
/*   Updated: 2023/11/06 18:48:18 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base.h"

void	ft_free_2d(void ***arr_ptr)
{
	void	**arr;

	if (!arr_ptr)
		return ;
	arr = *arr_ptr;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(*arr_ptr);
	*arr_ptr = NULL;
}
