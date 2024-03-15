#include "exec.h"
#include "exec_internal.h"

#include <stdbool.h>
#include <unistd.h>

#include "env.h"
#include "expansion.h"
#include "ft_error.h"
#include "global.h"

static int	exec_last_pipe_cmd(t_ast_node *cmd_node, t_pid_list **pids,
	int in_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		in_subprocess(1);
		if (expand_cmd_argv(cmd_node, ".", env()) != 0)
			handle_system_error(NULL, true);
		if (in_fd >= 0)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		exec_cmd(cmd_node);
	}
	pid_list_add(pids, pid);
	return (-1);
}

static int	exec_pipe_cmd(t_ast_node *cmd_node, t_pid_list **pids, int in_fd)
{
	pid_t	pid;
	int		_pipe[2];

	pipe(_pipe);
	pid = fork();
	if (pid == 0)
	{
		in_subprocess(1);
		if (expand_cmd_argv(cmd_node, ".", env()) != 0)
			handle_system_error(NULL, true);
		if (in_fd >= 0)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		dup2(_pipe[1], STDOUT_FILENO);
		close(_pipe[0]);
		close(_pipe[1]);
		exec_cmd(cmd_node);
	}
	pid_list_add(pids, pid);
	close(_pipe[1]);
	if (in_fd >= 0)
		close(in_fd);
	return (_pipe[0]);
}

static int	exec_last_pipe_subshell(t_ast_node *subshell_node,
	t_pid_list **pids, int in_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		in_subprocess(1);
		if (in_fd >= 0)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		exec_subshell(subshell_node);
	}
	pid_list_add(pids, pid);
	return (-1);
}

static int	exec_pipe_subshell(t_ast_node *subshell_node, t_pid_list **pids,
	int in_fd)
{
	pid_t	pid;
	int		_pipe[2];

	pipe(_pipe);
	pid = fork();
	if (pid == 0)
	{
		in_subprocess(1);
		if (in_fd >= 0)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		dup2(_pipe[1], STDOUT_FILENO);
		close(_pipe[0]);
		close(_pipe[1]);
		exec_subshell(subshell_node);
	}
	pid_list_add(pids, pid);
	close(_pipe[1]);
	if (in_fd >= 0)
		close(in_fd);
	return (_pipe[0]);
}

static int	exec_pipe(t_ast_node *pipe_node, t_pid_list **pids, bool is_last)
{
	int	in_fd;

	if (pipe_node->left->type == AST_CMD)
		in_fd = exec_pipe_cmd(pipe_node->left, pids, -1);
	else if (pipe_node->left->type == AST_SUBSHELL)
		in_fd = exec_pipe_subshell(pipe_node->left, pids, -1);
	else
		in_fd = exec_pipe(pipe_node->left, pids, false);
	if (pipe_node->right->type == AST_CMD && is_last)
		return (exec_last_pipe_cmd(pipe_node->right, pids, in_fd));
	else if (pipe_node->right->type == AST_CMD)
		return (exec_pipe_cmd(pipe_node->right, pids, in_fd));
	if (pipe_node->right->type == AST_SUBSHELL && is_last)
		return (exec_last_pipe_subshell(pipe_node->right, pids, in_fd));
	else
		return (exec_pipe_subshell(pipe_node->right, pids, in_fd));
}

int	exec_pipeline(t_ast_node *pipe_node)
{
	t_pid_list	*pids;
	int			exit_status;

	pids = NULL;
	exec_pipe(pipe_node, &pids, true);
	exit_status = pid_list_wait(pids);
	pid_list_destroy(pids);
	return (exit_status);
}