#include "redirection.h"

#include <stdlib.h>
#include <unistd.h>

#include "ft_error.h"
#include "token_list.h"

static t_redir_list *redir_list_create_node(t_token_type type, char *word,
	t_error *error)
{
	t_redir_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node)
	{
		new_node->next = NULL;
		new_node->type = type;
		new_node->heredoc_fd = -1;
		if (type == T_REDIR_HEREDOC)
		{
			new_node->file = NULL;
			new_node->heredoc_term = word;
		}
		else
		{
			new_node->file = word;
			new_node->heredoc_term = NULL;
		}
	}
	else
		error_set_system(error);
	return (new_node);
}

static t_redir_list	*redir_list_last(t_redir_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	redir_list_add(t_redir_list **list, t_token_type type, char *word,
	t_error *error)
{
	t_redir_list	*new_node;

	new_node = redir_list_create_node(type, word, error);
	if (has_error(error))
		return ;
	if (!*list)
		*list = new_node;
	else
		redir_list_last(*list)->next = new_node;
}

void	redir_list_destroy(t_redir_list *list)
{
	t_redir_list	*next_node;

	while (list)
	{
		next_node = list->next;
		free(list->file);
		free(list->heredoc_term);
		if (list->heredoc_fd > 2)
			close(list->heredoc_fd);
		free(list);
		list = next_node;
	}
}
