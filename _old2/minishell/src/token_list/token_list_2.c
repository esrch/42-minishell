#include "_minishell.h"

void	token_list_insert_after(t_token_list **token_list, t_token_list *insertion)
{
	t_token_list	*next;
	t_token_list	*last;

	if (!insertion)
		return ;
	if (!*token_list)
	{
		*token_list = insertion;
		return ;
	}
	next = (*token_list)->next;
	(*token_list)->next = insertion;
	insertion->prev = *token_list;
	last = token_list_last(insertion);
	last->next = next;
	if (next)
		next->prev = last;
}

void	token_list_remove(t_token_list **token_list, int count)
{
	int				remove_count;
	t_token_list	*prev;
	t_token_list	*current;
	t_token_list	*next;

	if (!token_list)
		return ;
	if (count < 1)
		return ;
	remove_count = 0;
	prev = (*token_list)->prev;
	current = *token_list;
	while (current && remove_count < count)
	{
		next = current->next;
		token_list_del(current);
		current = next;
		remove_count++;
	}
	if (prev)
		prev->next = current;
	if (next)
		current->prev = prev;
	if (!prev)
		*token_list = current;
}

void	token_list_replace(t_token_list **token_list, int count,
	t_token_list *insertion)
{
	t_token_list	*prev;

	if (!token_list)
		return ;
	prev = (*token_list)->prev;
	token_list_remove(token_list, count);
	if (!insertion)
		return ;
	if (prev)
		token_list_insert_after(&prev, insertion);
	else
	{
		token_list_last(insertion)->next = *token_list;
		*token_list = insertion;
	}
}