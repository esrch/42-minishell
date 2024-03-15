#include "exec.h"
#include "exec_internal.h"

#include "env.h"
#include "ft_error.h"
#include "ft_sprintf.h"
#include "global.h"
#include "libft.h"

static int	exec_builtin_export_print(void)
{
	char	**env_keys;
	char	**current;
	char	*value;

	env_keys = hash_map_keys(env());
	if (!env_keys)
	{
		ft_error_print_system(prog_name(NULL), "export");
		return (1);
	}
	current = env_keys;
	while (*current)
	{
		value = env_get(*current);
		if (value)
			ft_printf("declare -x %s=\"%s\"\n", *current, value);
		else
			ft_printf("declare -x %s\n", *current);
		current++;
	}
	ft_free_2d((void ***) &env_keys);
	return (0);
}

bool	is_valid_var_name(char *s)
{
	if (!*s)
		return (false);
	if (!ft_strchr("_" "abcdefghijklmnopqrstuvwxyz"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ", *s))
		return (false);
	s++;
	while (*s)
	{
		if (!ft_strchr("_" "abcdefghijklmnopqrstuvwxyz"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"0123456789", *s))
			return (false);
	}
	return (true);
}

void	print_invalid_var_name_error(char *key, char *value)
{
	char	*msg;

	if (value)
		msg = ft_sprintf("`%s=%s': not a valid identifier", key, value);
	else
		msg = ft_sprintf("`%s': not a valid identifier", key);
	if (!msg)
		ft_error_print_system(prog_name(NULL), "export");
	else
		ft_error_print_custom(prog_name(NULL), "export", msg);
	free(msg);
}

int	exec_builtin_export_set(char *key, char *value)
{
	int	result;

	result = 0;
	if (!is_valid_var_name(key))
	{
		print_invalid_var_name_error(key, value);
		return (-1);
	}
	if (value)
		result = env_set(key, value);
	else if (!env_get(key))
		result = env_set(key, value);
	if (result != 0)
	{
		ft_error_print_system(prog_name(NULL), "export");
		return (-1);
	}
	return (0);
}

int	exec_builtin_export(t_ast_node *cmd_node)
{
	int			result;
	t_word_list	*argv;
	char		*eq_pos;
	char		*value;

	result = 0;
	argv = cmd_node->cmd_argv->next;
	if (!argv)
		return (exec_builtin_export_print());
	while (argv)
	{
		eq_pos = ft_strchr(argv->word, '=');
		if (eq_pos)
		{
			*eq_pos = '\0';
			value = eq_pos + 1;
		}
		else
			value = NULL;
		if (exec_builtin_export_set(argv->word, value) != 0)
			result = 1;
		argv = argv->next;
	}
	return (result);
}
