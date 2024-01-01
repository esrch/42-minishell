#include "_minishell.h"

int	token_list_add_token(t_token_list **token_list, t_token *token)
{
	t_token_list	*new_node;
	t_token_list	*last;

	if (!token)
		return (-1);
	new_node = token_list_construct(token);
	if (!new_node)
		return (-1);
	if (!*token_list)
	{
		*token_list = new_node;
		return (0);
	}
	last = token_list_last(*token_list);
	last->next = new_node;
	return (0);
}

int	token_list_add_op(t_token_list **token_list, t_token_type token_type)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
		return (-1);
	token_init_op(token, token_type);
	if (token_list_add_token(token_list, token) < 0)
	{
		token_cleanup(token);
		free(token);
		return (-1);
	}
	return (0);
}

int	token_list_add_word(t_token_list **token_list, char *lexeme, char *value)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
		return (-1);
	token_init_word(token, lexeme, value);
	if (token_list_add_token(token_list, token) < 0)
	{
		token_cleanup(token);
		free(token);
		return (-1);
	}
	return (0);
}