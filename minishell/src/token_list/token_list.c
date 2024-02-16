#include "token_list.h"

#include <stdlib.h>

#include "libft.h"
#include "token.h"

/** Returns the last node of a list, or NULL for a NULL list.
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

/** Adds a token of operator type type to the given list.
 * 
 * Returns 0 in case of success, or -1 in case of allocation error.
*/
int	token_list_add_op(t_token_list **list, t_token_type type)
{
	t_token			*token;
	t_token_list	*new_node;

	if (!list)
		return (-1);
	token = token_create_op(type);
	if (!token)
		return (-1);
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
	{
		token_destroy(token);
		return (-1);
	}
	new_node->next = NULL;
	new_node->token = token;
	if (!*list)
		*list = new_node;
	else
		token_list_last(*list)->next = new_node;
	return (0);
}

/** Adds a word token with the given value of to the given list.
 * 
 * Returns 0 in case of success, or -1 in case of allocation error.
*/
int	token_list_add_word(t_token_list **list, char *value)
{
	t_token			*token;
	t_token_list	*new_node;

	if (!list)
		return (-1);
	token = token_create_word(value);
	if (!token)
		return (-1);
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
	{
		token_destroy(token);
		return (-1);
	}
	new_node->next = NULL;
	new_node->token = token;
	if (!*list)
		*list = new_node;
	else
		token_list_last(*list)->next = new_node;
	return (0);
}

/** Frees the memory allocated for the token list
 * 
*/
void	token_list_destroy(t_token_list *list)
{
	t_token_list	*next_node;

	while (list)
	{
		next_node = list->next;
		token_destroy(list->token);
		free(list);
		list = next_node;
	}
}

/** Prints the token list to standard out
 * 
 * Prints the list as a space separated list of token values.
*/
void	token_list_print(t_token_list *list)
{
	if (!list)
		return ;
	while (list->next)
	{
		ft_printf("%s ", list->token->value);
		list = list->next;
	}
	ft_printf("%s", list->token->value);
}
