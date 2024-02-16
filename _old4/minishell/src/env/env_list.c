#include "env_internal.h"

#include <stdlib.h>
#include <string.h>

#include "ft_error.h"

/** Creates a new node with key and value
 *
 * Returns the newly created node.
 * Errors:
 * - Allocation error: System error
**/
static t_env_list	*env_list_create_node(char *key, char *value, t_error *error)
{
	t_env_list	*new_node;

	if (!key)
		return (NULL);
	new_node = malloc(sizeof(*new_node));
	if (new_node)
	{
		new_node->next = NULL;
		new_node->key = key;
		new_node->value = value;
	}
	else
		error_set_system(error);
	return (new_node);
}

/** Returns the last element of a list
 *
**/
static t_env_list	*env_list_last(t_env_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/** Adds a new node to the list
 *
 * The key and value are first copied before being added to the list
 * Errors:
 * - Allocation error: System error
**/
void	env_list_add(t_env_list **list, char *key, char *value,
	t_error *error)
{
	char		*key_cpy;
	char		*value_cpy;
	t_env_list	*new_node;

	if (!list || !key)
		return ;
	key_cpy = strdup(key);
	value_cpy = strdup(value);
	if (!key_cpy || !value_cpy)
		error_set_system(error);
	if (!has_error(error))
		new_node = env_list_create_node(key_cpy, value_cpy, error);
	if (has_error(error))
	{
		free(key_cpy);
		free(value_cpy);
		return ;
	}
	if (!*list)
		*list = new_node;
	else
		env_list_last(*list)->next = new_node;
}

/** Updates the value in the given node
 *
 * Copies the new value before storing it.
 * Errors:
 * - Allocation error: System error
**/
void	env_list_update_node(t_env_list *node, char *value, t_error *error)
{
	char	*value_cpy;

	if (!node)
		return ;
	value_cpy = strdup(value);
	if (!value_cpy)
		error_set_system(error);
	else
		node->value = value_cpy;
}

/** Returns the first node with the requested key
 *
 * Returns the actual value stored, not a copy.
 * If no value is found, returns NULL.
**/
t_env_list	*env_list_find(t_env_list *list, char *key)
{
	int			key_len;

	if (!list || !key)
		return (NULL);
	key_len = strlen(key);
	while (list)
	{
		if (strncmp(key, list->key, key_len + 1) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

/** Frees the memory of the passed node
 *
**/
void	env_list_destroy_node(t_env_list *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

/** Frees the memory for all nodes of a list
 *
 * Frees the key and value of each node.
**/
void	env_list_destroy(t_env_list *list)
{
	t_env_list	*next_node;

	while (list)
	{
		next_node = list->next;
		env_list_destroy_node(list);
		list = next_node;
	}
}

/** Remove a new from a list
 *
**/
void	env_list_remove_node(t_env_list **node)
{
	t_env_list	*next_node;

	if (!node || !*node)
		return ;
	next_node = (*node)->next;
	env_list_destroy_node(*node);
	*node = next_node;
}

int	env_list_len(t_env_list *list)
{
	int i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}