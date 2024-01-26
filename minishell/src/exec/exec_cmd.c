#include "exec_internal.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_error.h"
#include "redirection_list.h"
#include "word_list.h"

static void	open_fd(t_redirection_list *redirection, int *new_fd, int *replaced_fd,
	t_error *error)
{
	if (redirection->type == REDIR_OUT)
	{
		new_fd = open(redirection->filename, O_CREAT | O_WRONLY);
		replaced_fd = STDOUT_FILENO;
	}
	else if (redirection->type == REDIR_APPEND)
	{
		new_fd = open(redirection->filename, O_CREAT | O_WRONLY | O_APPEND);
		replaced_fd = STDOUT_FILENO;
	}
	else if (redirection->type == REDIR_IN)
	{
		new_fd = open(redirection->filename, O_RDONLY);
		replaced_fd = STDOUT_FILENO;
	}
	else if (redirection->type == REDIR_HEREDOC)
	{
		new_fd = redirection->here_doc_fd;
		replaced_fd = STDIN_FILENO;
	}
	else
	{
		error_set_custom(error, ft_strdup(__FILE__ ": invalid redirection type"));
		return ;
	}
}

static void	setup_redirections(t_redirection_list *redirections, t_error *error)
{
	int	new_fd;
	int	replaced_fd;

	while (redirections)
	{
		open_fd(redirections, &new_fd, &replaced_fd, error);
		if (has_error(error))
			return ;
		if (new_fd < 0)
			error_set_system(error);
		if (!has_error(error) && dup2(new_fd, replaced_fd) < 0)
			error_set_system(error);
		if (!has_error(error) && close(new_fd) < 0)
			error_set_system(error);
		if (!has_error(error) && redirections->type == REDIR_HEREDOC)
			redirections->here_doc_fd = -1;
		if (has_error(error))
			return ;
	}
}

void	exec_cmd(t_ast_node *node)
{
	char	**argv;
	t_error	error;

	error_init(&error);
	setup_redirections(node->cmd_redirections, &error);
	if (!has_error(&error))
		argv = word_list_to_array(node->cmd_argv, &error);
	if (has_error(&error))
	{
		// Cleanup all data
		// Add correct prompt
		error_print(&error, NULL);
		error_cleanup(&error);
		exit(2);
	}
	execvp(argv[0], argv);
	ft_free_2d((void ***)&argv);
	// Add correct prompt
	perror(NULL);
	// Destroy full AST in case of error
	exit(2);
}

