#include "token_list.h"

#include <stdlib.h>
#include "libft.h"
#include "defines.h"
#include "token.h"
#include "ft_error.h"

static t_token_list	*create_node(t_token *token)
{
	t_token_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node)
	{
		new_node->token = token;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
	else
		error_print_system();
	return (new_node);
}

static void	destroy_node(t_token_list *node)
{
	token_destroy(node->token);
	free(node);
}

static t_token_list	*last_node(t_token_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

static t_status	add_token(t_token_list **list, t_token *token)
{
	t_token_list	*new_node;

	new_node = create_node(token);
	if (!new_node)
		return (STATUS_ERROR);
	if (!*list)
		*list = new_node;
	else
		last_node(*list)->next = new_node;
	return (STATUS_OK);
}

t_status	token_list_add_op(t_token_list **list, t_token_type type)
{
	t_token	*token;

	token = token_create_op(type);
	if (!token)
		return (STATUS_ERROR);
	if (add_token(list, token) == STATUS_ERROR)
	{
		token_destroy(token);
		return (STATUS_ERROR);
	}
	return (STATUS_OK);
}

t_status	token_list_add_word(t_token_list **list, char *value)
{
	t_token	*token;

	token = token_create_word(value);
	if (!token)
		return (STATUS_ERROR);
	if (add_token(list, token) == STATUS_ERROR)
	{
		token_destroy(token);
		return (STATUS_ERROR);
	}
	return (STATUS_OK);
}

void	token_list_clear(t_token_list *list)
{
	t_token_list	*next;

	while (list)
	{
		next = list->next;
		destroy_node(list);
		list = next;
	}
}

void	token_list_print(t_token_list *list)
{
	while (list)
	{
		token_print(list->token);
		if (list->next)
			ft_printf(" ");
		list = list->next;
	}
	ft_printf("\n");
}