#include "token_list.h"

#include <stdlib.h>

#include "libft.h"
#include "token.h"

/** Returns the length of the token list.
 * 
*/
size_t			token_list_len(t_token_list *list)
{
	size_t	len;

	len = 0;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}

/** Returns the node in the token list at the given index.
 * 
 * Returns the node, or NULL if the index is out of bounds.
*/
t_token_list	*token_list_at(t_token_list *list, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index && list)
	{
		i++;
		list = list->next;
	}
	return (list);
}

/** Prints the token list.
 * 
*/
void	token_list_print(t_token_list *list)
{
	while (list)
	{
		token_print(list->token);
		if (list->next)
			ft_printf(" ");
		else
			ft_printf("\n");
		list = list->next;
	}
}