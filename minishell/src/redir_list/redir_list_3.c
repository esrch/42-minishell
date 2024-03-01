#include "redir_list.h"

#include <unistd.h>
#include <readline/readline.h>

#include "libft.h"

/** Reads heredoc from stdin for the node, and sets the
 * node's fd to the read end of the pipe used.
 * 
*/
static void	read_heredoc(t_redir_list *node)
{
	int		_pipe[2];
	char	*line;

	pipe(_pipe);
	line = readline("> ");
	while (line && ft_strcmp(line, node->word) != 0)
	{
		write(_pipe[1], line, ft_strlen(line));
		write(_pipe[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(_pipe[1]);
	node->fd = _pipe[0];
}

/** Reads heredocs from stdin for each heredoc node in the list.
 * 
 * Sets the heredoc node's fd to the read end of the pipe used.
*/
void	redir_list_read_heredocs(t_redir_list *list)
{
	t_redir_list	*current;

	current = list;
	while (current)
	{
		if (current->type == T_REDIR_HEREDOC)
			read_heredoc(current);
		current = current->next;
	}
}
