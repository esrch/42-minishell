#include "heredoc_list.h"

#include <stdlib.h>

#include "redir_list.h"
#include "token.h"

/** Adds a redirection list node to the heredoc list.
 * 
 * If the node is NULL, does nothing and returns 0.
 * If the node is not a heredoc node, does nothing and returns 0. 
 * 
 * Returns 0 on success, or -1 on error.
*/
int	heredoc_list_add(t_heredoc_list **list, t_redir_list *heredoc_node)
{
	t_heredoc_list	*new_node;

	if (!list || !heredoc_node || heredoc_node->type != T_REDIR_HEREDOC)
		return (0);
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (-1);
	new_node->next = NULL;
	new_node->heredoc_node = heredoc_node;
	if (!*list)
		*list = new_node;
	else
		heredoc_list_last(*list)->next = new_node;
	return (0);
}

/** Frees the memory allocated for the list.
 * 
 * Does not close file descriptors of the heredocs in the list
 * (to do this, call heredoc_list_close_all).
 * Does not destroy the heredoc nodes contained in each element.
*/
void	heredoc_list_destroy(t_heredoc_list *list)
{
	t_heredoc_list	*next;

	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}

/** Returns the last node in the list, or NULL if the list is empty.
 * 
*/
t_heredoc_list	*heredoc_list_last(t_heredoc_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}
