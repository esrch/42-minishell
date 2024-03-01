#include "exec.h"
#include "exec_internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "env.h"
#include "expand.h"
#include "ft_error.h"
#include "ft_sprintf.h"
#include "global.h"
#include "libft.h"
#include "path.h"
#include "redirection.h"
#include "word_list.h"

/** Handle error if no executable file was found in the path.
 * 
*/
static void	handle_non_executable(char **argv, t_path_info path_info)
{
	if (!path_info.path)
	{
		error_print_custom(ft_sprintf( "%s: Command not found", argv[0]));
		exit(127);
	}
	if (!path_info.is_exec)
	{
		error_print_custom(ft_sprintf( "%s: Permission denied", path_info.path));
		exit(126);
	}
	exit(1);
}

/** Executes the actual command from a command node.
 * 
*/
static void execute(t_ast_node *node)
{
	char		**argv;
	t_path_info	path_info;
	char		**envp;

	argv = expand_argv(node->cmd_argv);
	envp = env_to_arr();
	if (!argv || !envp)
	{
		error_print_system(NULL);
		exit(1);
	}
	if (path_search(argv[0], env_get("PATH"), &path_info) != 0)
	{
		error_print_system(NULL);
		exit(1);
	}
	if (!path_info.path || !path_info.is_exec)
		handle_non_executable(argv, path_info);
	execve(path_info.path, argv, envp);
	error_print_system(path_info.path);
	exit(1);
}

/** Sets up the redirections if the command is part of a pipeline.
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

/** Executes a command AST node.
 * 
 * The command is executed in a separated process.
 * 
 * Returns the id of the process that executed the command.
*/
pid_t	exec_cmd(t_ast_node *node, int pipe_in_fd, int *pipe_out_fd)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe_out_fd)
	{
		(void)pipe(pipe_fd);
		*pipe_out_fd = pipe_fd[0];
	}
	pid = fork();
	if (pid == 0)
	{
		setup_pipe_in_out(pipe_in_fd, pipe_out_fd, pipe_fd);
		if (redirection_apply(node->redirections) != 0)
			exit(1);
		execute(node);
	}
	if (pipe_out_fd)
		close(pipe_fd[1]);
	return (pid);
}

/** Executes a command that is not part of a pipeline.
 * 
 * Returns the exit code of the command.
*/
int	exec_simple_cmd(t_ast_node *node)
{
	pid_t	child_pid;
	int		status;

	child_pid = exec_cmd(node, -1, NULL);
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);
}
