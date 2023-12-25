#include "token.h"

int	token_list_add(t_token_list **token_list, t_token *token)
{
	t_token_list	*new_elem;
	t_token_list	*current;

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
	current = *token_list;
	while(current->next)
		current = current->next;
	current->next = new_elem;
	return (0);
}

int	token_list_add_token_type(t_token_list **token_list,
	t_token_type token_type)
{
	return (token_list_add(token_list, token_construct(token_type, NULL, NULL)));
}

int	token_list_add_word(t_token_list **token_list, char *lexeme)
{
	return (token_list_add(token_list, token_construct(T_WORD, lexeme, NULL)));
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

	current = token_list;
	while (current)
	{
		if (current != token_list)
			printf(" ");
		token_print(current->token);
		current = current->next;
	}
	printf("\n");
}