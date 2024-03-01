#include "kv_list.h"

#include <stdbool.h>
#include <stdlib.h>

#include "libft.h"

static t_kv_list	*kv_list_last(t_kv_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/** Adds a key value pair to the list
 * 
 * The value may be NULL.
 * Allocates a copy of the key and value before saving.
 * The value is not copied if it is NULL.
 * Returns 0 on success, or -1 on allocation error.
*/
int		kv_list_add(t_kv_list **list, char *key, char *value)
{
	t_kv_list	*new_node;
	char		*key_cpy;
	char		*value_cpy;

	key_cpy = ft_strdup(key);
	value_cpy = NULL;
	if (value)
		value_cpy = ft_strdup(value);
	new_node = malloc(sizeof(*new_node));
	if (!key_cpy || (value && !value_cpy) || !new_node)
	{
		free(key_cpy);
		free(value_cpy);
		free(new_node);
		return (-1);
	}
	new_node->next = NULL;
	new_node->key = key_cpy;
	new_node->value = value_cpy;
	if (!*list)
		*list = new_node;
	else
		kv_list_last(*list)->next = new_node;
	return (0);
}

/** Updates the value of node.
 * 
 * The value may be NULL.
 * Allocates a copy of value before updating
 * (except if value is NULL);
 * Returns 0 on success, or -1 on allocation error.
*/
int	kv_list_update(t_kv_list *node, char *value)
{
	char	*value_cpy;

	if (!node)
		return (-1);
	if (!value)
	{
		free(node->value);
		node->value = NULL;
		return (0);
	}
	value_cpy = ft_strdup(value);
	if (!value_cpy)
		return (-1);
	free(node->value);
	node->value = value_cpy;
	return (0);
}

/** Frees the memory allocated for the list
 * 
*/
void	kv_list_destroy(t_kv_list *list)
{
	t_kv_list	*next_node;

	while (list)
	{
		next_node = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = next_node;
	}
}

/** Returns the number of elements in the list
 * 
*/
int		kv_list_len(t_kv_list *list)
{
	int	len;

	len = 0;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}
