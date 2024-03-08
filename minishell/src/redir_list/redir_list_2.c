#include "redir_list.h"

#include <fcntl.h>
#include <unistd.h>

#include "libft.h"

/** Opens a file if required according to the node type.
 * 
 * Returns the opened file's file descriptor. Could be -1 on error.
*/
static int	redir_list_open_file(t_redir_list *node)
{
	if (node->fd != -1)
		return (node->fd);
	if (node->type == T_REDIR_IN)
		return (open(node->word, O_RDONLY));
	if (node->type == T_REDIR_OUT)
		return open(node->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (node->type == T_REDIR_APPEND)
		return open(node->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (-1);
}

/** Redirects stdin or stdout according to the node type.
 * 
 * Assumes that the node's file descriptor (fd) is already set.
 * If not, no redirection is done.
*/
static void	redir_list_redirect(t_redir_list *node)
{
	if (node->fd < 0)
		return ;
	if (node->type == T_REDIR_IN || node->type == T_REDIR_HEREDOC)
		dup2(node->fd, STDIN_FILENO);
	else if (node->type == T_REDIR_OUT || node->type == T_REDIR_APPEND)
		dup2(node->fd, STDOUT_FILENO);
	close(node->fd);
	node->fd = -1;
}

/** Sets up the redirections in the list.
 * 
 * Applies the redirection of each node, opening the required
 * file if necessary.
 * 
 * Returns NULL on success, or the node that issued an error on error.
*/
t_redir_list	*redir_list_apply(t_redir_list *list)
{
	t_redir_list	*current;

	current = list;
	while (current)
	{
		if (current->fd == -1)
			current->fd = redir_list_open_file(current);
		if (current->fd == -1)
		{
			redir_list_close_all(list);
			return (current);
		}
		redir_list_redirect(current);
		current = current->next;
	}
	return (NULL);
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