#include "env.h"

#include <stdlib.h>

#include "libft.h"

static void	free_value(void *value)
{
	free(value);
}

/** Returns the global env hash map, or NULL on error.
 * 
*/
t_hash_map	*env(void)
{
	static t_hash_map	*env_value = NULL;

	if (!env_value)
		env_value = hash_map_create(free_value);
	return (env_value);
}

/** Frees the memory allocated for the environment.
 * 
*/
void	env_destroy(void)
{
	hash_map_destroy(env());
}

/** Sets an environment paramenter value for a given key.
 * 
 * The key and value are copied before being stored in the environment.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	env_set(char *key, char *value)
{
	t_hash_map	*env_value;
	char		*value_cpy;
	int			result;
	
	env_value = env();
	if (!env_value)
		return (-1);
	value_cpy = ft_strdup(value);
	if (!value_cpy)
		return (-1);
	result = hash_map_set(env_value, key, value_cpy);
	if (result != 0)
		free(value_cpy);
	return (result);
}

/** Unsets an environment key if it exists.
 * 
 * Does nothing if the key doesn't exist in the environment.
*/
void		env_unset(char *key)
{
	t_hash_map	*env_value;

	env_value = env();
	if (!env_value)
		return ;
	hash_map_unset(env_value, key);
}

/** Returns the value associated with the key in the environment.
 * 
 * Returns the value if found, or NULL if the key is not present.
*/
char		*env_get(char *key)
{
	t_hash_map	*env_value;

	env_value = env();
	if (!env_value)
		return (NULL);
	return ((char *) hash_map_get(env_value, key));
}
