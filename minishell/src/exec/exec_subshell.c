#include "exec_internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ft_error.h"
#include "redirection.h"

/** Executes a subnode of a subshell AST node.
 * 
 * Returns the exit code of that subnode execution.
*/
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
	else
		return (exec_simple_subshell(node));
	return (1);
}

/** Sets up the redirections if the subshell is part of a pipeline.
 * 
*/
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

/** Executes a subshell AST node.
 * 
 * node is the AST node for the subshell.
 * pipe_in_fd is the fd from which the subshell commands should read
 * if they are part of a pipeline.
 * pipe_out_fd is the fd to which the subshell commands should write
 * if they are part of a pipeline.
 * 
 * Returns the process id of the subshell process.
*/
pid_t	exec_subshell(t_ast_node *node, int pipe_in_fd, int *pipe_out_fd)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe_out_fd)
	{
		(void) pipe(pipe_fd);
		*pipe_out_fd = pipe_fd[0];
	}
	pid = fork();
	if (pid == 0)
	{
		setup_pipe_in_out(pipe_in_fd, pipe_out_fd, pipe_fd);
		if (redirection_apply(node->redirections) != 0)
			exit(1);
		exit(exec_subnode(node->left));
	}
	if (pipe_out_fd)
		close(pipe_fd[1]);
	return (pid);
}

/** Executes a subshell that is not part of a pipeline.
 * 
 * Returns the exit code of the last command of the subshell.
*/
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