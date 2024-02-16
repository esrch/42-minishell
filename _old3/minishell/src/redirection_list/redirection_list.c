#include "redirection_list.h"

#include <stdlib.h>
#include <unistd.h>
#include "ft_error.h"

static t_redirection_list	*create_node(t_redirection_type type,
	char *filename, char *here_doc_terminator)
{
	t_redirection_list	*node;

	node = malloc(sizeof(*node));
	if (node)
	{
		node->next = NULL;
		node->type = type;
		node->filename = filename;
		node->here_doc_terminator = here_doc_terminator;
		node->here_doc_fd = -1;
	}
	else
		error_print_system();
	return (node);
}

static void	destroy_node(t_redirection_list *node)
{
	free(node->filename);
	free(node->here_doc_terminator);
	if (node->here_doc_fd != -1)
		close(node->here_doc_fd);
	free(node);
}

static t_redirection_list	*last_node(t_redirection_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

static void	add_node(t_redirection_list **list, t_redirection_list *node)
{
	if (!list)
		*list = node;
	else
		last_node(*list)->next = node;
}

t_status	redirection_list_add_file(t_redirection_list **list, t_redirection_type type,
			char *file)
{
	t_redirection_list	*new_node;

	new_node = create_node(type, file, NULL);
	if (!new_node)
		return (STATUS_ERROR);
	add_node(list, new_node);
	return (STATUS_OK);
}

t_status	redirection_list_add_heredoc(t_redirection_list **list, char *terminator)
{
	t_redirection_list	*new_node;
	
	new_node = create_node(REDIR_HEREDOC, NULL, terminator);
	if (!new_node)
		return (STATUS_ERROR);
	add_node(list, new_node);
	return (STATUS_OK);
}

void	redirection_list_clear(t_redirection_list *list)
{
	t_redirection_list	*next;

	while (list)
	{
		next = list->next;
		destroy_node(list);
		list = next;
	}
}
