#include "exec_internal.h"

#include <fcntl.h>
#include <unistd.h>

#include "ft_error.h"
#include "redirection.h"

static void	open_fd(t_redir_list *redirection, int *new_fd, int *replaced_fd,
	t_error *error)
{
	if (redirection->type == T_REDIR_OUT)
	{
		*new_fd = open(redirection->file, O_CREAT | O_WRONLY, 0644);
		*replaced_fd = STDOUT_FILENO;
	}
	else if (redirection->type == T_REDIR_APPEND)
	{
		*new_fd = open(redirection->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		*replaced_fd = STDOUT_FILENO;
	}
	else if (redirection->type == T_REDIR_IN)
	{
		*new_fd = open(redirection->file, O_RDONLY);
		*replaced_fd = STDIN_FILENO;
	}
	else
	{
		*new_fd = redirection->heredoc_fd;
		*replaced_fd = STDIN_FILENO;
	}
	if (*new_fd < 0)
		error_set_system(error);
}

void	setup_redirections(t_redir_list *redirections, t_error *error)
{
	int	new_fd;
	int	replaced_fd;

	while (redirections)
	{
		open_fd(redirections, &new_fd, &replaced_fd, error);
		if (!has_error(error) && dup2(new_fd, replaced_fd) < 0)
			error_set_system(error);
		if (!has_error(error) && close(new_fd) < 0)
			error_set_system(error);
		if (has_error(error))
			return ;
		if (redirections->type == T_REDIR_HEREDOC)
			redirections->heredoc_fd = -1;
		redirections = redirections->next;
	}
}