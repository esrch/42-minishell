#include "exec.h"
#include "exec_internal.h"

#include <unistd.h>

#include "ast.h"
#include "env.h"
#include "ft_error.h"
#include "libft.h"
#include "global.h"
#include "word_list.h"

int	exec_builtin_pwd(t_ast_node *cmd_node)
{
	char	*cwd;

	(void) cmd_node;
	cwd = getcwd(NULL, 0);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	exec_builtin_cd(t_ast_node *cmd_node)
{
	t_word_list	*argv;
	char		*cwd;

	argv = cmd_node->cmd_argv->next;
	if (!argv)
		return (0);
	if (word_list_len(argv) > 1)
	{
		ft_error_print_custom(prog_name(NULL), "cd", "too many arguments");
		return (1);
	}
	if (chdir(argv->word) != 0)
	{
		ft_error_print_system(prog_name(NULL), "cd");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (env_set("PWD", cwd) != 0)
	{
		free(cwd);
		ft_error_print_system(prog_name(NULL), "cd");
		return (1);
	}
	free(cwd);
	return (0);
}

int	exec_builtin_echo(t_ast_node *cmd_node)
{
	bool		add_newline;
	t_word_list	*argv;

	add_newline = true;
	argv = cmd_node->cmd_argv->next;
	if (!argv)
	{
		ft_printf("\n");
		return (0);
	}
	if (ft_strcmp(argv->word, "-n") == 0)
	{
		argv = argv->next;
		add_newline = false;
	}
	while (argv)
	{
		ft_printf("%s", argv->word);
		if (argv->next)
			ft_printf(" ");
		argv = argv->next;
	}
	if (add_newline)
		ft_printf("\n");
	return (0);
}

static bool	is_number(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

int	exec_builtin_exit(t_ast_node *cmd_node)
{
	t_word_list	*argv;

	argv = cmd_node->cmd_argv->next;
	if (in_subprocess(-1) == 0)
		ft_printf("exit\n");
	if (word_list_len(argv) > 1)
	{
		ft_error_print_custom(prog_name(NULL), "exit", "too many arguments");
		return (1);
	}
	if (!argv)
		exit(last_exit_status(-1));
	if (!is_number(argv->word))
	{
		ft_error_print_custom(prog_name(NULL), "exit", "numerical argument required");
		exit(2);
	}
	exit (ft_atoi(argv->word));
}