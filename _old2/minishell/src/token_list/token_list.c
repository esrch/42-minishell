#include "_minishell.h"

void	token_list_del(t_token_list *node)
{
	token_destroy(node->token);
	free(node);
}

void	token_list_clear(t_token_list **token_list)
{
	t_token_list	*current;

	while (*token_list)
	{
		current = *token_list;
		*token_list = current->next;
		token_list_del(current);
	}
}

t_token_list	*token_list_last(t_token_list *token_list)
{
	t_token_list	*last_node;

	if (!token_list)
		return (NULL);
	last_node = token_list;
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}

t_token_list	*token_list_at(t_token_list *token_list, int index)
{
	int				i;
	t_token_list	*current;

	if (!token_list)
		return (NULL);
	if (index < 0)
		return (NULL);
	i = 0;
	current = token_list;
	while (current && i++ < index)
		current = current->next;
	return (current);
}