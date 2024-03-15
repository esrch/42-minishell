#include "exec.h"
#include "exec_internal.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "env.h"
#include "expansion.h"
#include "ft_error.h"
#include "ft_sprintf.h"
#include "libft.h"
#include "path.h"
#include "global.h"
#include "redir_list.h"
#include "word_list.h"

static char	*get_exec_path(char *word)
{
	t_error		*error;
	t_word_list	*paths;
	t_path_info	path_info;

	error = ft_error_create();
	paths = path_build_list(env_get("PATH"), word, error);
	if (ft_has_error(error))
	{
		ft_error_destroy(error);
		handle_system_error(word, true);
	}
	ft_error_destroy(error);
	path_info = path_find(paths);
	if (!path_info.full_path)
		handle_cmd_not_found(word, true);
	if (!path_info.is_exec)
		handle_permission_denied(word, true);
	return (path_info.full_path);
}

static void	expand_redirection_word(t_redir_list *node)
{
	t_error		*error;
	t_word_list	*expanded_word;

	error = ft_error_create();
	expanded_word = expand_word(node->word, ".", env(), error);
	if (ft_has_error(error))
	{
		ft_error_destroy(error);
		handle_system_error(NULL, true);
	}
	ft_error_destroy(error);
	if (word_list_len(expanded_word) != 1)
		handle_ambiguous_redirect(node->word, true);
	node->word = ft_strdup(expanded_word->word);
	word_list_destroy(expanded_word);
	if (!node->word)
		handle_system_error(NULL, true);
}

static void	apply_redirections(t_redir_list *redirections)
{
	t_redir_list	*current;
	t_redir_list	*error_redirection;

	current = redirections;
	while (current)
	{
		expand_redirection_word(current);
		current = current->next;
	}
	error_redirection = redir_list_apply(redirections);
	if (error_redirection)
		handle_system_error(error_redirection->word, true);
}

void	exec_cmd(t_ast_node *cmd_node)
{
	char	**envp;
	char	**argv;
	char	*exec_path;

	apply_redirections(cmd_node->redirections);
	envp = env_to_arr();
	argv = word_list_to_arr(cmd_node->cmd_argv);
	if (!argv[0])
		exit (0);
	exec_path = get_exec_path(argv[0]);
	execve(exec_path, argv, envp);
	handle_system_error(NULL, true);
}

int	exec_simple_cmd(t_ast_node *cmd_node)
{
	pid_t		pid;
	t_pid_list	*pids;
	int			exit_status;

	if (expand_cmd_argv(cmd_node, ".", env()) != 0)
	{
		ft_error_print_system(prog_name(NULL), NULL);
		return (1);
	}
	if (cmd_node->cmd_argv == NULL)
		return (0);
	if (is_builtin(cmd_node->cmd_argv->word))
		return (exec_builtin(cmd_node));
	pids = NULL;
	pid = fork();
	if (pid == 0)
	{
		in_subprocess(1);
		exec_cmd(cmd_node);
	}
	pid_list_add(&pids, pid);
	exit_status = pid_list_wait(pids);
	pid_list_destroy(pids);
	return (exit_status);
}