#include "redirection.h"

#include <unistd.h>
#include <readline/readline.h>

#include "libft.h"

/** Reads lines to a pipe, and returns the file descriptor to the read end.
 * 
 * prompt is the prompt displayed when reading a line.
 * eof is the token that ends the reading.
 * 
 * Returns the file descriptor to read end of the pipe, or -1 on error.
*/
static int	read_to_pipe(char *prompt, char *eof)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) != 0)
		return (-1);
	line = readline(prompt);
	while (line && ft_strcmp(line, eof) != 0)
	{
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
		line = readline(prompt);
	}
	free(line);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

/** Sets up heredoc for each element in the redirection list.
 * 
 * Sets up pipes to read each heredoc.
 * Returns 0 on success, or -1 on error.
*/
int		heredoc_read(t_redir_list *list)
{
	while (list)
	{
		if (list->type == T_REDIR_HEREDOC)
			list->fd = read_to_pipe("> ", list->word);
		if (list->fd < 0)
			return (-1);
		list = list->next;
	}
	return (0);
}
