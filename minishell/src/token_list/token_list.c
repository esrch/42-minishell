#include "token_list.h"

#include <stdlib.h>

/** Returns the last node in the token list,
 * or NULL if the list is empty.
 * 
*/
static t_token_list	*token_list_last(t_token_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/** Adds a new token at the end of the token list.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	token_list_add(t_token_list **list, t_token *token)
{
	t_token_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (-1);
	new_node->token = token;
	new_node->next = NULL;
	if (!*list)
		*list = new_node;
	else
		token_list_last(*list)->next = new_node;
	return (0);
}

/** Adds a new operator token at the end of the token list.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	token_list_add_op(t_token_list **list, t_token_type type)
{
	t_token	*token;
	int		result;
	
	token = token_create_op(type);
	if (!token)
		return (-1);
	result = token_list_add(list, token);
	if (result != 0)
		token_destroy(token);
	return (result);
}

int	token_list_add_word(t_token_list **list, char *value)
{
	t_token	*token;
	int		result;
	
	token = token_create_word(value);
	if (!token)
		return (-1);
	result = token_list_add(list, token);
	if (result != 0)
		token_destroy(token);
	return (result);
}

/** Frees the memory allocated for a token list.
 * 
*/
void	token_list_destroy(t_token_list *list)
{
	t_token_list	*next;

	while (list)
	{
		next= list->next;
		token_destroy(list->token);
		free(list);
		list = next;
	}
}
