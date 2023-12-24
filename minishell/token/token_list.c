#include "token.h"

t_token_list	*token_list_add(t_token_list **token_list, t_token *token)
{
	t_token_list	*new_elem;
	t_token_list	*current;

	new_elem = malloc(sizeof(*new_elem));
	if (!new_elem)
		return (NULL);
	new_elem->token = token;
	new_elem->next = NULL;
	if (!*token_list)
	{
		*token_list = new_elem;
		return (new_elem);
	}
	current = *token_list;
	while(current->next)
		current = current->next;
	current->next = new_elem;
	return (new_elem);
	
}

void	token_list_clear(t_token_list **token_list)
{
	t_token_list	*current;

	while (*token_list)
	{
		current = *token_list;
		*token_list = current->next;
		token_destruct(current->token);
		free(current);
	}
}