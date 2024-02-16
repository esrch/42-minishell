#include "redirection.h"

#include <fcntl.h>
#include <unistd.h>

/** Opens file according to redirection node type.
 * 
 * Returns the file descriptor of the opened file,
 * or -1 on error.
*/
static int	open_file(t_redir_list *node)
{
	if (node->type == T_REDIR_IN)
		return open(node->word, O_RDONLY);
	else if (node->type == T_REDIR_OUT)
		return open(node->word, O_WRONLY | O_CREAT);
	else if (node->type == T_REDIR_APPEND)
		return open(node->word, O_WRONLY | O_CREAT | O_APPEND);
	else
		return node->fd;
}

/** Replaces standard in or out with redirection node.
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	setup_redirection(t_redir_list *node)
{
	int	result;

	if (node->type == T_REDIR_IN || node->type == T_REDIR_HEREDOC)
		result = dup2(node->fd, STDIN_FILENO);
	else
		result = dup2(node->fd, STDOUT_FILENO);
	if (result != 0)
		return (-1);
	close(node->fd);
	node->fd = -1;
	return (0);
}

/** Sets up all redirections in the list.
 * 
 * Returns 0 on success, or -1 on error.
*/
int		redirection_apply(t_redir_list *list)
{
	while (list)
	{
		list->fd = open_file(list);
		if (list->fd < 0)
			return (-1);
		if (setup_redirection(list) < 0)
			return (-1);
		close(list->fd);
		list->fd = -1;
		list = list->next;
	}
	return (0);
}
