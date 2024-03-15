#include "exec.h"
#include "exec_internal.h"

#include <stdio.h>
#include <unistd.h>

#include "ft_error.h"
#include "env.h"
#include "expansion.h"
#include "libft.h"
#include "global.h"
#include "redir_list.h"

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

static int	exec_subnode(t_ast_node *subnode)
{
	if (subnode->type == AST_AND)
		return (exec_and(subnode));
	if (subnode->type == AST_OR)
		return (exec_or(subnode));
	if (subnode->type == AST_SUBSHELL)
		return (exec_simple_subshell(subnode));
	if (subnode->type == AST_CMD)
		return (exec_simple_cmd(subnode));
	else if (subnode->type == AST_PIPE)
		return (exec_pipeline(subnode));
	return (0);
}

int	exec_subshell(t_ast_node *subshell_node)
{
	apply_redirections(subshell_node->redirections);
	exit(exec_subnode(subshell_node->left));
}

int	exec_simple_subshell(t_ast_node *subshell_node)
{
	pid_t		pid;
	t_pid_list	*pids;
	int			exit_status;

	pids = NULL;
	pid = fork();
	if (pid == 0)
	{
		in_subprocess(1);
		exec_subshell(subshell_node);
	}
	pid_list_add(&pids, pid);
	exit_status = pid_list_wait(pids);
	pid_list_destroy(pids);
	return (exit_status);
}