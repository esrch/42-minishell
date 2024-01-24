#include "token_list.h"

#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "ft_error.h"

static t_token_list	*create_node(t_token *token, t_error *error)
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
		error_set_system(error);
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

static void	add_token(t_token_list **list, t_token *token, t_error *error)
{
	t_token_list	*new_node;

	new_node = create_node(token, error);
	if (has_error(error))
		return ;
	if (!*list)
		*list = new_node;
	else
		last_node(*list)->next = new_node;
}

void	token_list_add_op(t_token_list **list, t_token_type type, t_error *error)
{
	t_token	*token;

	token = token_create_op(type, error);
	if (has_error(error))
		return ;
	add_token(list, token, error);
	if (has_error(error))
		token_destroy(token);
}

void	token_list_add_word(t_token_list **list, char *value, t_error *error)
{
	t_token	*token;

	token = token_create_word(value, error);
	if (has_error(error))
		return ;
	add_token(list, token, error);
	if (has_error(error))
		token_destroy(token);
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
	// Remove dependency on printf
	while (list)
	{
		token_print(list->token);
		if (list->next)
			printf(" ");
		list = list->next;
	}
	printf("\n");
}