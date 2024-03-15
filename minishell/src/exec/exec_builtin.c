#include "exec.h"
#include "exec_internal.h"

#include <stdbool.h>

#include "ast.h"
#include "env.h"
#include "expansion.h"
#include "ft_error.h"
#include "libft.h"

bool	is_builtin(char *word)
{
	return (ft_strcmp(word, "echo") == 0
		|| ft_strcmp(word, "cd") == 0
		|| ft_strcmp(word, "pwd") == 0
		|| ft_strcmp(word, "export") == 0
		|| ft_strcmp(word, "unset") == 0
		|| ft_strcmp(word, "env") == 0
		|| ft_strcmp(word, "exit") == 0);
}

static int	expand_redirection_word(t_redir_list *node)
{
	t_error		*error;
	t_word_list	*expanded_word;

	error = ft_error_create();
	expanded_word = expand_word(node->word, ".", env(), error);
	if (ft_has_error(error))
	{
		ft_error_destroy(error);
		handle_system_error(NULL, false);
		return (-1);
	}
	ft_error_destroy(error);
	if (word_list_len(expanded_word) != 1)
	{
		handle_ambiguous_redirect(node->word, false);
		return (-1);
	}
	node->word = ft_strdup(expanded_word->word);
	word_list_destroy(expanded_word);
	if (!node->word)
	{
		handle_system_error(NULL, false);
		return (-1);
	}
	return (0);
}

static int	apply_redirections(t_redir_list *redirections)
{
	t_redir_list	*current;
	t_redir_list	*error_redirection;

	current = redirections;
	while (current)
	{
		if (expand_redirection_word(current) != 0)
			return (-1);
		current = current->next;
	}
	error_redirection = redir_list_apply(redirections);
	if (error_redirection)
	{
		handle_system_error(error_redirection->word, false);
		return (-1);
	}
	return (0);
}

int	exec_builtin(t_ast_node *cmd_node)
{
	if (apply_redirections(cmd_node->redirections) != 0)
		return (1);
	if (ft_strcmp("cd", cmd_node->cmd_argv->word) == 0)
		return (exec_builtin_cd(cmd_node));
	else if (ft_strcmp("pwd", cmd_node->cmd_argv->word) == 0)
		return (exec_builtin_pwd(cmd_node));
	else if (ft_strcmp("echo", cmd_node->cmd_argv->word) == 0)
		return (exec_builtin_echo(cmd_node));
	else if (ft_strcmp("env", cmd_node->cmd_argv->word) == 0)
		return (exec_builtin_env(cmd_node));
	else if (ft_strcmp("export", cmd_node->cmd_argv->word) == 0)
		return (exec_builtin_export(cmd_node));
	else if (ft_strcmp("unset", cmd_node->cmd_argv->word) == 0)
		return (exec_builtin_unset(cmd_node));
	else if (ft_strcmp("exit", cmd_node->cmd_argv->word) == 0)
		return (exec_builtin_exit(cmd_node));
	return (0);
}
