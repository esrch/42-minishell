#include "exec.h"
#include "exec_internal.h"

#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

static int	wait_pids(t_pid_list *pid_list)
{
	int		status;
	int		exit_status;
	pid_t	pid;
	pid_t	last_pid;

	exit_status = 0;
	last_pid = pid_list_last(pid_list)->pid;
	while (pid_list)
	{
		pid = waitpid(0, &status, 0);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = WTERMSIG(status);
		}
		pid_list = pid_list->next;
	}
	return (exit_status);
}

static void	redirect_std_in_out(int in_fd, int out_fd)
{
	if (in_fd > -1)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd > -1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

static int exec_first_pipe(t_ast_node *node, t_pid_list **pid_list, bool is_last)
{
	int		internal_pipe_fd[2];
	int		outgoing_pipe_fd[2];
	pid_t	child_pid1;
	pid_t	child_pid2;

	pipe(internal_pipe_fd);
	child_pid1 = fork();
	if (child_pid1 == 0)
	{
		close(internal_pipe_fd[0]);
		pid_list_destroy(*pid_list);
		redirect_std_in_out(-1, internal_pipe_fd[1]);
		exec_cmd(node->left);
	}
	close(internal_pipe_fd[1]);
	if (!is_last)
		pipe(outgoing_pipe_fd);
	child_pid2 = fork();
	if (child_pid2 == 0)
	{
		if (!is_last)
			close(outgoing_pipe_fd[0]);
		pid_list_destroy(*pid_list);
		if (is_last)
		{
			redirect_std_in_out(internal_pipe_fd[0], -1);
			exec_cmd(node->left);
		}
		else
		{
			redirect_std_in_out(internal_pipe_fd[0], outgoing_pipe_fd[1]);
			exec_cmd(node->left);
		}
	}
	close(internal_pipe_fd[0]);
	if (!is_last)
		close(outgoing_pipe_fd[1]);
	pid_list_add(pid_list, child_pid1);
	pid_list_add(pid_list, child_pid2);
	if (is_last)
		return (-1);
	else
		return (outgoing_pipe_fd[0]);
}

static int	exec_pipe(t_ast_node *node, t_pid_list **pid_list, bool is_last)
{
	int		in_fd;
	int		pipe_fd[2];
	pid_t	child_pid;

	if (node->left->type == AST_CMD)
		return (exec_first_pipe(node, pid_list, is_last));
	in_fd = exec_pipe(node->left, pid_list, false);
	if (!is_last)
		pipe(pipe_fd);
	child_pid = fork();
	if (child_pid == 0)
	{
		if (!is_last)
			close(pipe_fd[0]);
		pid_list_destroy(*pid_list);
		if (is_last)
		{
			redirect_std_in_out(in_fd, -1);
			exec_cmd(node->right);
		}
		else
		{
			redirect_std_in_out(in_fd, pipe_fd[1]);
			exec_cmd(node->right);
		}
	}
	close(in_fd);
	if (!is_last)
		close(pipe_fd[1]);
	pid_list_add(pid_list, child_pid);
	if (is_last)
		return (-1);
	else
		return (pipe_fd[0]);
}

int exec_pipeline(t_ast_node *node)
{
	t_pid_list	*pid_list;
	int			exit_status;

	pid_list = NULL;
	exec_pipe(node, &pid_list, true);
	exit_status = wait_pids(pid_list);
	pid_list_destroy(pid_list);
	return (exit_status);
}