#include "_minishell.h"

static t_token_list	*token_list_construct(t_token *token, t_error *error)
{
	t_token_list	*token_list;

	token_list = malloc(sizeof(*token_list));
	if (!token_list)
	{
		error_set(error, ERR_SYSTEM, NULL);
		return (NULL);
	}
	token_list->prev = NULL;
	token_list->next = NULL;
	token_list->token = token;
	return (token_list);
}

static void	token_list_add_token(t_token_list **token_list, t_token *token, t_error *error)
{
	t_token_list	*new_node;
	t_token_list	*last;

	if (!token)
	{
		error_set(error, ERR_CUSTOM,
			ft_strdup("token_list_add_token: Cannot call with NULL token"));
		return ;
	}
	new_node = token_list_construct(token, error);
	if (has_error(error))
		return ;
	if (!*token_list)
	{
		*token_list = new_node;
		return ;
	}
	last = token_list_last(*token_list);
	last->next = new_node;
	new_node->prev = last;
}

void	token_list_add_op(t_token_list **token_list, t_token_type token_type, t_error *error)
{
	t_token	*token;

	token = token_create_op(token_type);
	if (!token)
	{
		error_set(error, ERR_SYSTEM, NULL);
		return ;
	}
	token_list_add_token(token_list, token, error);
	if (has_error(error))
		token_destroy(token);
}

void	token_list_add_word(t_token_list **token_list, char *value, t_error *error)
{
	t_token	*token;

	token = token_create_word(value);
	if (!token)
	{
		error_set(error, ERR_SYSTEM, NULL);
		return ;
	}
	token_list_add_token(token_list, token, error);
	if (has_error(error))
		token_destroy(token);
}