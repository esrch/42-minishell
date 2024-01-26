/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_count.c                                  :+:      :+:    :+:  */
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
	int		i;
	void	**arr;

	i = 0;
	arr = *arr_ptr;
	while (i < count)
	{
		free(*arr);
		i++;
		arr++;
	}
	free(*arr_ptr);
	*arr_ptr = NULL;
}
