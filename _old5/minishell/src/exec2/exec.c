#include "exec.h"
#include "exec_internal.h"

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "ast.h"
#include "dyn_arr.h"

void	exec_cmd(t_ast_node *node)
{
	// Expand redirection parameters
	// Setup redirections
	// Expand parameters
	// Execute
}

int	exec_simple_cmd(t_ast_node *cmd_node)
{
	pid_t		pid;
	t_pid_list	*pid_list;
	int			exit_status;

	pid_list = NULL;
	pid = fork();
	if (pid == 0)
		exec_cmd(cmd_node);
	pid_list_add(pid_list, pid);
	exit_status = wait_pids(pid_list);
	pid_list_destroy(pid_list);
	return (exit_status);
}

void	exec_subshell(t_ast_node *subshell_node, t_pid_list **pid_list)
{
	pid_t	pid;
	int		_pipe[2];

	pipe(_pipe);
	pid = fork();
	if (pid == 0)
	{
		dup2(_pipe[1], STDOUT_FILENO);
		close(_pipe[0]);
		close(_pipe[1]);
		if (redirection_apply(subshell_node->redirections) != 0)
			exit(1);
		if (subshell_node->left->type == AST_CMD)
			exit(exec_simple_cmd(subshell_node->left));
		exit(exec_boundary(subshell_node->left));
	}
	pid_list_add(pid_list, pid);
}

void	exec_pipe_cmd(t_ast_node *cmd_node, t_pid_list **pid_list)
{
	int		_pipe[2];
	pid_t	pid;

	pipe(_pipe);
	pid = fork();
	if (pid == 0)
	{
		dup2(_pipe[1], STDOUT_FILENO);
		close(_pipe[0]);
		close(_pipe[1]);
		exec_cmd(cmd_node);
		exit(1);
	}
	pid_list_add(pid_list, pid);
	close(_pipe[1]);
	dup2(_pipe[0], STDIN_FILENO);
}

void	exec_pipe(t_ast_node *pipe_node, t_pid_list **pid_list)
{
	if (pipe_node->left->type == AST_PIPE)
		exec_pipe(pipe_node->left, pid_list);
	else if (pipe_node->left->type == AST_CMD)
		exec_pipe_cmd(pipe_node->left, pid_list);
	else
		exec_subshell(pipe_node->left, pid_list);
	if (pipe_node->right->type == AST_CMD)
		exec_pipe_cmd(pipe_node->right, pid_list);
	else
		exec_subshell(pipe_node->right, pid_list);
}

int	exec_boundary(t_ast_node *node)
{
	int			stdin_cpy;
	t_pid_list	*pid_list;
	int			exit_status;

	stdin_cpy = dup(STDIN_FILENO);
	pid_list = NULL;
	if (node->type == AST_PIPE)
		exec_pipe(node, &pid_list);
	else
		exec_subshell(node, &pid_list);
	exit_status = wait_pids(pid_list);
	flush_pipe(STDIN_FILENO, STDOUT_FILENO);
	dup2(stdin_cpy, STDIN_FILENO);
	close(stdin_cpy);
	pid_list_destroy(pid_list);
	return (exit_status);
}

int	exec_and(t_ast_node *and)
{

}