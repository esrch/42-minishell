/* ************************************************************************** */
/*									    */
/*							:::      ::::::::   */
/*   utils.c					    :+:      :+:    :+:   */
/*						    +:+ +:+	 +:+     */
/*   By: erabbath <erabbath@42lausanne.ch>	  +#+  +:+       +#+	*/
/*						+#+#+#+#+#+   +#+	   */
/*   Created: 2023/07/11 08:51:02 by erabbath	  #+#    #+#	     */
/*   Updated: 2023/07/12 07:35:44 by erabbath	 ###   ########.fr       */
/*									    */
/* ************************************************************************** */

#include "ft_printf_internal.h"

size_t	ft_strlen_max(char *str, size_t max)
{
	size_t	i;

	i = 0;
	while (str[i] && i < max)
		i++;
	return (i);
}
