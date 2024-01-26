#include "exec_internal.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "defines.h"
#include "libft.h"
#include "ft_error.h"
#include "global.h"
#include "redirection_list.h"
#include "word_list.h"

static t_status	open_fd(t_redirection_list *redirection, int *new_fd, int *replaced_fd)
{
	if (redirection->type == REDIR_OUT)
	{
		*new_fd = open(redirection->filename, O_CREAT | O_WRONLY);
		*replaced_fd = STDOUT_FILENO;
	}
	else if (redirection->type == REDIR_APPEND)
	{
		*new_fd = open(redirection->filename, O_CREAT | O_WRONLY | O_APPEND);
		*replaced_fd = STDOUT_FILENO;
	}
	else if (redirection->type == REDIR_IN)
	{
		*new_fd = open(redirection->filename, O_RDONLY);
		*replaced_fd = STDOUT_FILENO;
	}
	else
	{
		*new_fd = redirection->here_doc_fd;
		*replaced_fd = STDIN_FILENO;
	}
	if (*new_fd < 0)
	{
		error_print_system();
		return (STATUS_ERROR);
	}
	return (STATUS_OK);
}

static t_status	setup_redirections(t_redirection_list *redirections)
{
	int	new_fd;
	int	replaced_fd;

	while (redirections)
	{
		if (open_fd(redirections, &new_fd, &replaced_fd) == STATUS_ERROR)
			return (STATUS_ERROR);
		if (dup2(new_fd, replaced_fd) < 0)
		{
			error_print_system();
			return (STATUS_ERROR);
		}
		if (close(new_fd) < 0)
		{
			error_print_system();
			return (STATUS_ERROR);
		}
		if (redirections->type == REDIR_HEREDOC)
			redirections->here_doc_fd = -1;
	}
	return (STATUS_OK);
}

void	exec_cmd(t_ast_node *node)
{
	char	**argv;

	if (setup_redirections(node->cmd_redirections) == STATUS_ERROR)
		exit(2);
	argv = word_list_to_array(node->cmd_argv);
	if (!argv)
	{
		global_clean();
		exit(2);
	}
	execvp(argv[0], argv);
	ft_free_2d((void ***)&argv);
	error_print_system();
	global_clean();
	exit(2);
}
