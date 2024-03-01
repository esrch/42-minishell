#include "token_list.h"

#include <stdlib.h>

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
