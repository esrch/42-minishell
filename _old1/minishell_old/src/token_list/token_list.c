#include "minishell.h"

int	token_list_add(t_token_list **token_list, t_token *token)
{
	t_token_list	*new_elem;
	t_token_list	*last;

	if (!token)
		return (-1);
	new_elem = malloc(sizeof(*new_elem));
	if (!new_elem)
		return (-1);
	new_elem->token = token;
	new_elem->next = NULL;
	if (!*token_list)
	{
		*token_list = new_elem;
		return (0);
	}
	last = token_list_last(*token_list);
	last->next = new_elem;
	return (0);
}

t_token_list	*token_list_last(t_token_list *token_list)
{
	t_token_list	*current;

	if (!token_list)
		return (NULL);
	current = token_list;
	while (current->next)
		current = current->next;
	return (current);
}

int	token_list_add_token_type(t_token_list **token_list,
	t_token_type token_type)
{
	t_token	*token;

	token = token_construct(token_type, NULL, NULL);
	if (!token)
		return (-1);
	if (token_list_add(token_list, token) < 0)
	{
		token_destruct(token);
		return (-1);
	}
	return (0);
}

int	token_list_add_word(t_token_list **token_list, char *lexeme, char *value)
{
	t_token	*token;

	token = token_construct(T_WORD, lexeme, value);
	if (!token)
		return (-1);
	if (token_list_add(token_list, token) < 0)
	{
		token_destruct(token);
		return (-1);
	}
	return (0);
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

void	token_list_print(t_token_list *token_list)
{
	t_token_list	*current;
	char			*token_str;

	current = token_list;
	while (current)
	{
		if (current != token_list)
			printf(" ");
		token_str = token_tostring(current->token);
		ft_printf("%s", token_str);
		free(token_str);
		current = current->next;
	}
	printf("\n");
}