#include "redirection.h"

#include <unistd.h>

#include "libft.h"

/** Sets up individual heredoc node
 * 
 * Reads from standard in into a pipe, and assigns the
 * output file descriptor to heredoc_node->fd.
 * Returns 0 on success, or -1 on error
*/
static int	setup_heredoc(t_redir_list *heredoc_node)
{
	int		pipe_fd[2];
	int		eof_len;
	char	*line;

	if (pipe(pipe_fd) != 0)
		return (-1);
	eof_len = ft_strlen(heredoc_node->word);
	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, heredoc_node->word, eof_len + 1) != 0)
	{
		write(pipe_fd[1], line, ft_strlen(line));
		line = get_next_line(STDIN_FILENO);
	}
	close(pipe_fd[1]);
	heredoc_node->fd = pipe_fd[0];
	return (0);
}

/** Sets up heredoc for each element in the list.
 * 
 * Sets up pipes to read each heredoc.
 * Returns 0 on success, or -1 on error.
*/
int		heredoc_read(t_redir_list *list)
{
	int	result;

	while (list)
	{
		if (list->type == T_REDIR_HEREDOC)
			result = setup_heredoc(list);
		if (result != 0)
			return (-1);
		list = list->next;
	}
	return (0);
}
