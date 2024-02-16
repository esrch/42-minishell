#include "env.h"
#include "env_internal.h"

#include <stdlib.h>
#include <unistd.h>

#include "ft_error.h"
#include "libft.h"
#include "ft_sprintf_malloc.h"

/** Returns the address of the statically stored environment
 *
**/
static t_env_list	**get_env(void)
{
	static t_env_list	*env = NULL;

	return (&env);
}

/** Initializes the PWD environment variable to the
 * current directory
 *
**/
static void env_init_pwd(t_error *error)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	env_set("PWD", pwd, error);
	free(pwd);
}

/** Initializes the default value for SHLVL
 *
**/
static void	env_init_shlvl(t_error *error)
{
	char	*shlvl;
	char	*shlvl_cpy;
	int		new_shlvl_val;
	char	new_shlvl_val_str[3];

	shlvl = env_get("SHLVL");
	if (!shlvl)
	{
		env_set("SHLVL", "1", error);
		return ;
	}
	shlvl_cpy = shlvl;
	if (*shlvl_cpy == '+' || *shlvl_cpy == '-')
		shlvl_cpy++;
	while (*shlvl_cpy)
	{
		if (*shlvl_cpy < '0' || *shlvl_cpy > '9')
		{
			env_set("SHLVL", "1", error);
			return ;
		}
		shlvl_cpy++;
	}
	new_shlvl_val = ft_atoi(shlvl) + 1;
	if (new_shlvl_val < 0)
		env_set("SHLVL", "0", error);
	else if (new_shlvl_val > 99)
		env_set("SHLVL", "1", error);
	else
	{
		// Change to use itoa
		new_shlvl_val_str[2] = '\0';
		if (new_shlvl_val > 9)
			new_shlvl_val_str[1] = new_shlvl_val / 10 + '0';
		else
			new_shlvl_val_str[1] = '\0';
		new_shlvl_val_str[0] = new_shlvl_val % 10 + '0';
		env_set("SHLVL", new_shlvl_val_str, error);
	}
}

/** Initializes default required values for the environment
 *
 * The default values set are PWD and SHLVL
 * Errors:
 * - Allocation error: System error
 *
**/
static void	env_init_default(t_error *error)
{
	env_init_pwd(error);
	if (!has_error(error))
		env_init_shlvl(error);
}

/** Initializes the environment
 *
 * Errors:
 * - Allocation error: System error
**/
void	env_init(char **envp, t_error *error)
{
	char	*eq_pos;

	if (!envp)
		return ;
	while (*envp)
	{
		eq_pos = ft_strchr(*envp, '=');
		if (eq_pos)
		{
			*eq_pos = '\0';
			env_set(*envp, eq_pos + 1, error);	
			*eq_pos = '=';
		}
		if (has_error(error))
		{
			env_destroy();
			return ;
		}
		envp++;
	}
	env_init_default(error);
}

/** Reinitialized the environment
 *
**/
void	env_destroy(void)
{
	t_env_list	**env;

	env = get_env();
	env_list_destroy(*env);
	*env = NULL;
}

/** Returns the environment variable associated with key
 * or NULL if not found.
 *
 * Returns the actual value, not a copy.
**/
char	*env_get(char *key)
{
	t_env_list	**env;
	t_env_list	*found_node;

	if (!key)
		return (NULL);
	env = get_env();
	found_node = env_list_find(*env, key);
	if (!found_node)
		return (NULL);
	return (found_node->value);
}

/** Updates or adds a value associated with a key in the
 * environment.
 *
 * Copies the key and value before storing them.
 * Errors:
 * - Allocation error: System error
**/
void	env_set(char *key, char *value, t_error *error)
{
	t_env_list	**env;
	t_env_list	*found_node;

	if (!key)
		return ;
	env = get_env();
	found_node = env_list_find(*env, key);
	if (found_node)
		env_list_update_node(found_node, value, error);
	else
		env_list_add(env, key, value, error);
}

/** Removes an entry associated with a key in the environment
 *
**/
void	env_unset(char *key)
{
	t_env_list	**env;
	t_env_list	**current_node;
	int			key_len;

	if (!key)
		return ;
	env = get_env();
	if (!*env)
		return ;
	current_node = env;
	key_len = ft_strlen(key);
	while (*current_node)
	{
		if (ft_strncmp((*current_node)->key, key, key_len + 1) == 0)
		{
			env_list_remove_node(current_node);
			return ;
		}
		current_node = &(*current_node)->next;
	}
}

static void	set_arr_val(t_env_list *node, char **arr, int i, t_error *error)
{
	if (node->value)
		arr[i] = ft_sprintf_malloc("%s=%s", node->key, node->value);
	else
		arr[i] = ft_sprintf_malloc("%s", node->key);
	if (!arr[i])
	{
		error_set_system(error);
		while (i--)
			free(arr[i]);
		free(arr);
	}
}

char	**env_to_arr(t_error *error)
{
	char		**arr;
	t_env_list	*env;
	int			i;
	int			env_len;

	env = *(get_env());
	env_len = env_list_len(env);
	arr = malloc(sizeof(*arr) * (env_len + 1));
	if (!arr)
	{
		error_set_system(error);
		return (NULL);
	}
	i = 0;
	while (env)
	{
		set_arr_val(env, arr, i, error);
		if (has_error(error))
			return (NULL);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}