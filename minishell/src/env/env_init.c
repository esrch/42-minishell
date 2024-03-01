#include "env.h"

#include <stdio.h>

#include "libft.h"

/** Adds a key value pair from an envp line to the environment.
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	env_add_from_envp(char *line)
{
	char	*eq_pos;
	int		result;

	eq_pos = ft_strchr(line, '=');
	if (!eq_pos)
		return (0);
	*eq_pos = '\0';
	result = env_set(line, eq_pos + 1);
	*eq_pos = '=';
	return (result);
}

/** Initializes the PWD environment variable.
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	env_init_pwd(void)
{
	char	*pwd;
	int		result;

	pwd = getcwd(NULL, 0);
	result = env_set("PWD", pwd);
	free(pwd);
	return (result);
}

/** Sets the SHLVL environment variable.
 * 
 * 
*/
static int	env_init_shlvl(void)
{
	char	*shlvl;
	int		shlvl_val;
	char	*new_shlvl;
	int		result;

	shlvl = env_get("SHLVL");
	if (!shlvl || !*shlvl)
		return (env_set("SHLVL", "1"));
	shlvl_val = ft_atoi(shlvl);
	if (shlvl_val < 0)
		return (env_set("SHLVL", "0"));
	if (shlvl_val == 99)
		return (env_set("SHLVL", ""));
	if (shlvl_val > 99)
		return (env_set("SHLVL", "1"));
	new_shlvl = ft_itoa(shlvl_val + 1);
	if (!new_shlvl)
		return (-1);
	result = env_set("SHLVL", new_shlvl);
	free(new_shlvl);
	return (result);
}

/** Initializes the environment based on the envp received from main.
 * 
 * Returns 0 on success, and -1 on error.
*/
int	env_init(char **envp)
{
	t_hash_map	*env_value;

	env_value = env();
	if (!env_value)
		return (-1);
	while (envp && *envp)
	{
		if (env_add_from_envp(*envp) != 0)
		{
			env_destroy();
			return (-1);
		}
		envp++;
	}
	if (env_init_pwd() != 0
		|| env_init_shlvl() != 0)
	{
		env_destroy();
		return (-1);
	}
	return (0);
}
