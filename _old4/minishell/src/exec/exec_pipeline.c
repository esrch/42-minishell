#include "exec_internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ast.h"

static void exec_pipe(t_ast_node *node, t_pid_list **pid_list, int *out_fd)
{
	pid_t 	pid;
	int 	in_fd;
	t_error	error;

	if (node->left->type == AST_CMD)
	{
		pid = exec_cmd(node->left, -1, &in_fd);
		pid_list_add(pid_list, pid, &error);
		// Handle the error properly
	}
	else if (node->left->type == AST_SUBSHELL)
	{
		pid = exec_subshell(node->left, -1, &in_fd);
		pid_list_add(pid_list, pid, &error);
		// Handle the error
	}
	else
		exec_pipe(node->left, pid_list, &in_fd);
	if (node->right->type == AST_CMD)
		pid = exec_cmd(node->right, in_fd, out_fd);
	else
		pid = exec_subshell(node->right, in_fd, out_fd);
	pid_list_add(pid_list, pid, &error);
	// Handle error
	close(in_fd);
}

static int	wait_pids(t_pid_list *pid_list)
{
	int		status;
	int		exit_status;
	pid_t	pid;
	pid_t	last_pid;

	exit_status = 0;
	last_pid = pid_list_last(pid_list)->pid;

	// Debug
	t_pid_list *pid_list_cpy = pid_list;
	while (pid_list_cpy)
	{
		pid_list_cpy = pid_list_cpy->next;
	}
	
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

int exec_pipeline(t_ast_node *node)
{
	t_pid_list	*pid_list;
	int			exit_status;

	pid_list = NULL;
	exec_pipe(node, &pid_list, NULL);
	exit_status = wait_pids(pid_list);
	pid_list_destroy(pid_list);
	return (exit_status);
}