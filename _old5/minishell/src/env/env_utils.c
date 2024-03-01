#include "env.h"
#include "env_internal.h"

#include "libft.h"

/** Sets the key-value pair in the environment.
 * 
 * Updates the value if the key already exists,
 * otherwise adds the key value pair.
 * Copies the key and value before storing.
 * Returns 0 on success, or -1 on allocation error.
*/
int		env_set(char *key, char *value)
{
	t_kv_list	**env;
	t_kv_list	*current_node;

	env = env_value();
	current_node = *env;
	while (current_node)
	{
		if (ft_strcmp(current_node->key, key) == 0)
			return (kv_list_update(current_node, value));
		current_node = current_node->next;
	}
	return (kv_list_add(env, key, value));
}

/** Removes the key-value pair from the environment.
 * 
 * No action if the key doesn't exist.
*/
void	env_unset(char *key)
{
	t_kv_list	**env;
	t_kv_list	*current_node;
	t_kv_list	*prev_node;

	env = env_value();
	current_node = *env;
	prev_node = NULL;
	if (!current_node || !key)
		return ;
	while (current_node && ft_strcmp(current_node->key, key) != 0)
	{
		prev_node = current_node;
		current_node = current_node->next;
	}
	if (!current_node)
		return ;
	if (!prev_node)
		*env = current_node->next;
	else
		prev_node->next = current_node->next;
	current_node->next = NULL;
	kv_list_destroy(current_node);
}

/** Returns the environment value for a specific key.
 * 
 * Returns the stored value, not a copy.
*/
char	*env_get(char *key)
{
	t_kv_list	**env;
	t_kv_list	*current_node;

	env = env_value();
	current_node = *env;
	if (!current_node || !key)
		return (NULL);
	while (current_node)
	{
		if (ft_strcmp(current_node->key, key) == 0)
			return (current_node->value);
		current_node = current_node->next;
	}
	return (NULL);
}

static char	*kv_to_str(t_kv_list *node)
{
	int		len;
	char	*str;

	if (node->value)
		len = ft_strlen(node->key) + ft_strlen(node->value) + 1;
	else
		len = ft_strlen(node->key);
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, node->key, len + 1);
	if (node->value)
	{
		ft_strlcat(str, "=", len + 1);
		ft_strlcat(str, node->value, len + 1);
	}
	return (str);
}

/** Converts the environment to a NULL-terminated array of strings.
 * 
 * Returns the array on success, or NULL on error.
*/
char	**env_to_arr(void)
{
	t_kv_list	**env;
	t_kv_list	*current_node;
	char		**arr;
	int			i;
	char		*kv_str;

	env = env_value();
	arr = malloc(sizeof(*arr) * (kv_list_len(*env) + 1));
	if (!arr)
		return (NULL);
	current_node = *env;
	i = 0;
	while (current_node)
	{
		kv_str = kv_to_str(current_node);
		if (!kv_str)
		{
			ft_free_2d_count((void ***) &arr, i);
			return (NULL);
		}
		arr[i++] = kv_str;
		current_node = current_node->next;
	}
	arr[i] = NULL;
	return (arr);
}
