#include "exec.h"
#include "exec_internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "env.h"
#include "ft_error.h"
#include "ft_sprintf_malloc.h"
#include "global.h"
#include "libft.h"
#include "path.h"
#include "word_list.h"

/*
static void	prepare_cmd(t_ast_node *cmd_node, t_error *error)
{
	// Expand params
	expand_params(cmd_node, error);
	if (!has_error(error))
		split_cmd_words(cmd_node, error);
	// Expand wildcard
	// Split words
	// Get full executable path
}
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

static void	execute(t_ast_node *node)
{
	t_error		error;
	char		**argv;
	char		**env;
	t_path_info	path_info;

	error_init(&error);
	path_info = path_search(argv[0], env_get("PATH"), &error);
	global_cleanup();
	if (has_error(&error))
	{
		error_print(&error);
		error_cleanup(&error);
		exit(1);
	}
	if (!path_info.path)
	{
		error_print_custom(ft_sprintf_malloc( "%s: Command not found", node->cmd_argv[0]));
		exit(127);
	}
	if (!path_info.is_exec)
	{
		error_print_custom(ft_sprintf_malloc( "%s: Permission denied", node->cmd_argv[0]));
		exit(126);
	}
	argv = word_list_to_arr(node->cmd_argv_list, &error);
	if (has_error(&error))
	{
		free(path_info.path);
		error_print(&error);
		error_cleanup(&error);
		exit(1);
	}
	env = env_to_arr(&error);
	if (has_error(&error))
	{
		free(path_info.path);
		ft_free_2d(argv);
		error_print(&error);
		error_cleanup(&error);
		exit(1);
	}
	execve(path_info.path, argv, env);
	free(path_info.path);
	ft_free_2d(argv);
	ft_free_2d(env);
	error_print_system();
	exit(1);
}

pid_t	exec_cmd(t_ast_node *node, int pipe_in_fd, int *pipe_out_fd)
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
			global_cleanup();
			// Clean up pid_list
			exit(2);
		}
		execute(node);
	}
	if (pipe_out_fd)
		close(pipe_fd[1]);
	return (pid);
}

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
