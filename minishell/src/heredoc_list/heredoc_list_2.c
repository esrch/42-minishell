#include "heredoc_list.h"

#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "libft.h"

/** Reads from stdin and forwards the text to write_fd.
 * 
*/
static void	read_heredoc_exec(char *eof, int write_fd)
{
	char	*line;
	size_t	len;

	line = 0;
	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	if (line)
		len = ft_strlen(line);
	while (line && ft_strncmp(eof, line, len - 1) != 0)
	{
		write(write_fd, line, len);
		free(line);
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line)
			len = ft_strlen(line);
	}
	free(line);
}

/** Wait for the given pid.
 * 
 * Returns 0 on success (exit code = 0),
 * -1 on error (exit code = 0),
 * or -2 if the process was terminated with SIGINT.
*/
static int	read_heredoc_wait(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			return (0);
		else
			return (-1);
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (-2);
	return (0);
}

/** Reads there heredoc for a specific node.
 * 
 * Returns 0 on success, -1 on error, or -2 if reading the heredoc
 * was interrupted by a SIGINT signal.
*/
static int	read_heredoc(t_redir_list *heredoc_node)
{
	int		return_val;
	int		_pipe[2];
	pid_t	pid;

	if (pipe(_pipe) != 0)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(_pipe[0]);
		read_heredoc_exec(heredoc_node->word, _pipe[1]);
		exit(0);
	}
	close(_pipe[1]);
	return_val = read_heredoc_wait(pid);
	if (return_val == 0)
		heredoc_node->fd = _pipe[0];
	return (return_val);
}

/** Reads the heredoc for each element in the list,
 * and sets the fd for each heredoc node.
 * 
 * Does this by creating a pipe, transfering text read from stdin
 * into the pipe, and assigning the read end of the pipe to the
 * heredoc node fd.
 * Each heredoc read is executed in a separate process, so that it can be
 * interrupted with a signal.
 * 
 * Returns 0 on success, -1 if there was an error, or -2 if reading a
 * heredoc was interrupted by SIGINT.
*/
int	heredoc_list_read(t_heredoc_list *list)
{
	int	result;

	while (list)
	{
		result = read_heredoc(list->heredoc_node);
		if (result != 0)
			return (result);
		list = list->next;
	}
	return (0);
}