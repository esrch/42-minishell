#include "redir_list.h"

#include <stdlib.h>
#include <unistd.h>

#include "token.h"

/** Adds a redirection to the redirection list.
 * 
 * If the token type is not a redirection, no node is added,
 * but no error is returned.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	redir_list_add(t_redir_list **list, t_token_type type, char *word)
{
	t_redir_list	*new_node;

	if (!token_is_redirection_type(type))
		return (0);
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (-1);
	new_node->next = NULL;
	new_node->type = type;
	new_node->word = word;
	new_node->fd = -1;
	if (!*list)
		*list = new_node;
	else
		redir_list_last(*list)->next = new_node;
	return (0);
}

/** Frees the allocated memory of the redirection list.
 * 
 * Any open file descriptors (fd == -1) are closed first.
*/
void	redir_list_destroy(t_redir_list *list)
{
	t_redir_list	*next;

	while (list)
	{
		next = list->next;
		free(list->word);
		if (list->fd != -1)
			close(list->fd);
		free(list);
		list = next;
	}
}

/** Returns the last node in the redirection list,
 * or NULL if the list is empty.
 * 
*/
t_redir_list	*redir_list_last(t_redir_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/** Closes all redirections in the list that have fd != -1.
 * 
*/
void	redir_list_close_all(t_redir_list *list)
{
	while (list)
	{
		if (list->fd != -1)
		{
			close(list->fd);
			list->fd = -1;
		}
		list = list->next;
	}
}