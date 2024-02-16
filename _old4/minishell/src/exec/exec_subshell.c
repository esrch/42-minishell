#include "exec_internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ft_error.h"

static int	exec_subnode(t_ast_node *node)
{
	if (node->type == AST_AND)
		return (exec_and(node));
	else if (node->type == AST_OR)
		return (exec_or(node));
	else if (node->type == AST_PIPE)
		return (exec_pipeline(node));
	else if (node->type == AST_CMD)
		return (exec_simple_cmd(node));
	else if (node->type == AST_SUBSHELL)
		return (exec_simple_subshell(node));
	// Remove dependency on fprintf
	fprintf(stderr, "Invalid AST node\n");
	return (1);
}

static void	setup_pipe_in_out(int pipe_in_fd, int *pipe_out_fd, int *pipe_fd)
{
	if (pipe_in_fd >= 0)
	{
		dup2(pipe_in_fd, STDIN_FILENO);
		close(pipe_in_fd);
	}
	if (pipe_out_fd)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

pid_t	exec_subshell(t_ast_node *node, int pipe_in_fd, int *pipe_out_fd)
{
	pid_t	pid;
	int		pipe_fd[2];
	t_error	error;

	if (pipe_out_fd)
	{
		(void)pipe(pipe_fd);
		*pipe_out_fd = pipe_fd[0];
	}
	pid = fork();
	if (pid == 0)
	{
		error_init(&error);
		setup_pipe_in_out(pipe_in_fd, pipe_out_fd, pipe_fd);
		setup_redirections(node->cmd_redir, &error);
		if (has_error(&error))
		{
			error_print(&error);
			error_cleanup(&error);
			exit(2);
		}
		exit(exec_subnode(node->left));
	}
	if (pipe_out_fd)
		close(pipe_fd[1]);
	return (pid);
}

int	exec_simple_subshell(t_ast_node *node)
{
	pid_t	pid;
	int		status;

	pid = exec_subshell(node, -1, NULL);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);
}