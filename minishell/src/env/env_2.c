#include "env.h"

#include "libft.h"

/** Fills the given array from the environment
 * based on the list of keys passed as argument.
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	fill_arr(char **arr, char **keys)
{
	char	*env_value;
	size_t	len;

	while (*keys)
	{
		env_value = env_get(*keys);
		if (!env_value)
		{
			keys++;
			continue;
		}
		len = ft_strlen(*keys) + ft_strlen(env_value) + 1;
		*arr = malloc(sizeof(char) * (len + 1));
		if (!*arr)
			return (-1);
		ft_strlcpy(*arr, *keys, len + 1);
		ft_strlcat(*arr, "=", len + 1);
		ft_strlcat(*arr, env_value, len + 1);
		keys++;
		arr++;
	}
	*arr = NULL;
	return (0);
}

/** Converts the environment to a string array,
 * with keys and values separated by '='.
 * 
 * Entries with a NULL value are ignored.
 * 
 * Returns the array on success, or NULL on error.
*/
char	**env_to_arr(void)
{
	char		**arr;
	t_hash_map	*env_value;
	size_t		len;
	char		**keys;

	env_value = env();
	len = hash_map_count(env_value);
	arr = malloc(sizeof(*arr) * (len + 1));
	if (!arr)
		return (NULL);
	keys = hash_map_keys(env_value);
	if (!keys)
	{
		free(arr);
		return (NULL);
	}
	if (fill_arr(arr, keys) != 0)
	{
		ft_free_2d((void ***) &keys);
		ft_free_2d((void ***) &arr);
		return (NULL);
	}
	ft_free_2d((void ***) &keys);
	return (arr);
}