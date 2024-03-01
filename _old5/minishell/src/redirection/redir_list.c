#include "redirection.h"

#include <stdlib.h>

#include "libft.h"

/** Returns the last node of the list, or NULL for an empty list
 * 
*/
static t_redir_list	*redir_list_last(t_redir_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/** Add a redirection to the given list.
 * 
 * A copy of the word is allocated before saving.
 * Returns 0 on success, or -1 on allocation error.
*/
int	redir_list_add(t_redir_list **list, t_token_type type, char	*word)
{
	t_redir_list	*new_node;
	char			*word_cpy;

	if (!list)
		return (-1);
	new_node = malloc(sizeof(*new_node));
	word_cpy = ft_strdup(word);
	if (!new_node || !word_cpy)
	{
		free(new_node);
		free(word_cpy);
		return (-1);
	}
	new_node->next = NULL;
	new_node->type = type;
	new_node->word = word_cpy;
	new_node->fd = -1;
	if (!*list)
		*list = new_node;
	else
		redir_list_last(*list)->next = new_node;
	return (0);
}

/** Frees the memory allocated to the list
 * 
 * Closes any file descriptors in the list
*/
void	redir_list_destroy(t_redir_list *list)
{
	t_redir_list	*next_node;

	while (list)
	{
		next_node = list->next;
		free(list->word);
		if (list->fd >= 0)
			close(list->fd);
		free(list);
		list = next_node;
	}
}

/** Prints the redirection list
 * 
*/
void	redir_list_print(t_redir_list *list)
{
	while (list)
	{
		if (list->type == T_REDIR_IN)
			ft_printf("%s(<)", list->word);
		else if (list->type == T_REDIR_OUT)
			ft_printf("%s(>)", list->word);
		else if (list->type == T_REDIR_HEREDOC)
			ft_printf("%s(<<)", list->word);
		else
			ft_printf("%s(>>)", list->word);
		if (list->next)
			ft_printf(" ");
		list = list->next;
	}
}
