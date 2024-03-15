#include "exec.h"
#include "exec_internal.h"

#include "ast.h"
#include "env.h"
#include "ft_error.h"
#include "global.h"
#include "hash_map.h"
#include "libft.h"

int	exec_builtin_env(t_ast_node *cmd_node)
{
	char	**env_keys;
	char	**current;
	char	*value;

	(void) cmd_node;
	env_keys = hash_map_keys(env());
	if (!env_keys)
	{
		ft_error_print_system(prog_name(NULL), "env");
		return (1);
	}
	current = env_keys;
	while (*current)
	{
		value = env_get(*current);
		if (value)
			ft_printf("%s=%s\n", *current, value);
		current++;
	}
	ft_free_2d((void ***) &env_keys);
	return (0);
}

int	exec_builtin_unset(t_ast_node *cmd_node)
{
	t_word_list	*argv;

	argv = cmd_node->cmd_argv->next;
	while (argv)
	{
		env_unset(argv->word);
		argv = argv->next;
	}
	return (0);
}
