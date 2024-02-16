#include "env.h"
#include "env_internal.h"

#include <stdlib.h>

#include "kv_list.h"
#include "libft.h"

/** Returns the global env value address.
 * 
*/
t_kv_list	**env_value(void)
{
	static t_kv_list	*env = NULL;

	return (&env);
}

/** Initializes the environment from envp.
 * 
 * Returns 0 on success, or -1 on allocation error.
*/
int		env_init(char **envp)
{
	t_kv_list	**env;
	char		*eq_pos;
	int			result;

	env = env_value();
	while (*envp)
	{
		eq_pos = ft_strchr(*envp, '=');
		if (eq_pos)
		{
			*eq_pos = '\0';
			result = kv_list_add(env, *envp, eq_pos + 1);
			*eq_pos = '=';
			if (result != 0)
			{
				kv_list_destroy(*env);
				return (-1);
			}
		}
		envp++;
	}
	return (0);
}

/** Frees the memory allocated for the environment.
 * 
*/
void	env_destroy(void)
{
	t_kv_list	**env;

	env = env_value();
	kv_list_destroy(*env);
}
