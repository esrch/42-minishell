#include "token_list.h"

#include <stdlib.h>

#include "ft_error.h"
#include "libft.h"

static t_token_list	*last_node(t_token_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

static char	*get_op_value(t_token_type type, t_error *error)
{
	char	*value;

	if (type == T_AND)
		value = ft_strdup("&&");
	else if (type == T_OR)
		value = ft_strdup("||");
	else if (type == T_PAREN_OPEN)
		value = ft_strdup("(");
	else if (type == T_PAREN_CLOSE)
		value = ft_strdup(")");
	else if (type == T_PIPE)
		value = ft_strdup("|");
	else if (type == T_REDIR_IN)
		value = ft_strdup("<");
	else if (type == T_REDIR_HEREDOC)
		value = ft_strdup("<<");
	else if (type == T_REDIR_OUT)
		value = ft_strdup(">");
	else if (type == T_REDIR_APPEND)
		value = ft_strdup(">>");
	else if (type == T_EOF)
		value = ft_strdup("newline");
	else
		value = ft_strdup("");
	if (!value)
		error_set_system(error);
	return (value);
}

void	token_list_add(t_token_list **list, t_token_type type, char *value, t_error *error)
{
	t_token_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
	{
		error_set_system(error);
		return ;
	}
	new_node->type = type;
	new_node->value = value;
	new_node->next = NULL;
	if (!*list)
		*list = new_node;
	else
		last_node(*list)->next = new_node;
}

void	token_list_add_op(t_token_list **list, t_token_type type, t_error *error)
{
	char	*value;

	value = get_op_value(type, error);
	if (has_error(error))
		return ;
	else
		token_list_add(list, type, value, error);
}

void	token_list_destroy(t_token_list *list)
{
	t_token_list	*next;

	while (list)
	{
		next = list->next;
		free(list->value);
		free(list);
		list = next;
	}
}

bool	token_list_is_redir(t_token_list *node)
{
	return (
		node->type == T_REDIR_IN
		|| node->type == T_REDIR_HEREDOC
		|| node->type == T_REDIR_OUT
		|| node->type == T_REDIR_APPEND);
}

bool	token_list_is_and_or(t_token_list *node)
{
	return (node->type == T_AND || node->type == T_OR);
}

void	token_list_print(t_token_list *list)
{
	while (list)
	{
		ft_printf("%s", list->value);
		if (list->next)
			ft_printf(" ");
		list = list->next;
	}
	ft_printf("\n");
}