#include "hash_map.h"
#include "hash_map_internal.h"

#include <stdlib.h>

#include "libft.h"

/** Returns the hash element in the given map corresponding to the given key
 * 
 * Returns the found element, or NULL if none is found.
*/
static t_hash_elem	*hash_map_get_elem(t_hash_map *map, char *key)
{
	size_t		hash_index;
	t_hash_elem	*elem;

	hash_index = hash_map_hash_index(map->table_size, key);
	elem = map->table[hash_index];
	while (elem && ft_strcmp(key, elem->key) != 0)
		elem = elem->next;
	return (elem);
}

/** Creates a new hash element with the given key and value.
 * 
 * Returns the new element, or NULL on error.
*/
static t_hash_elem	*hash_elem_create(char *key, void *value)
{
	t_hash_elem	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem)
		return (NULL);
	elem->key = ft_strdup(key);
	if (!elem->key)
	{
		free(elem);
		return (NULL);
	}
	elem->value = value;
	return (elem);
}

/** Updates or adds the given value for the given key.
 * 
 * If the key already exists, the value is updated.
 * Otherwise, a new key-value pair is added to the map.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	hash_map_set(t_hash_map *map, char *key, void *value)
{
	size_t		hash_index;
	t_hash_elem	*elem;

	if (!map || !key)
		return (0);
	if (((double) map->elem_count) / map->table_size >= MAX_LOAD_FACTOR
		&& (hash_map_resize(map) != 0))
			return (-1);
	elem = hash_map_get_elem(map, key);
	if (elem)
	{
		if (map->destroy_value)
			map->destroy_value(elem->value);
		elem->value = value;
		return (0);
	}
	elem = hash_elem_create(key, value);
	if (!elem)
		return (-1);
	hash_index = hash_map_hash_index(map->table_size, key);
	elem->next = map->table[hash_index];
	map->table[hash_index] = elem;
	map->elem_count++;
	return (0);
}

/** Returns the value associated with a given key.
 * 
 * Returns the value if the key was found, otherwise NULL.
*/
void	*hash_map_get(t_hash_map *map, char *key)
{
	t_hash_elem	*elem;

	if (!map || !key)
		return (NULL);
	elem = hash_map_get_elem(map, key);
	if (!elem)
		return (NULL);
	return (elem->value);
}

/** Removes a key-value pair from the hash map, if found.
 * 
*/
void	hash_map_unset(t_hash_map *map, char *key)
{
	size_t		hash_index;
	t_hash_elem	*elem;
	t_hash_elem	*prev;

	hash_index = hash_map_hash_index(map->table_size, key);
	elem = map->table[hash_index];
	prev = NULL;
	while (elem && ft_strcmp(key, elem->key) != 0)
	{
		prev = elem;
		elem = elem->next;
	}
	if (!elem)
		return ;
	if (!prev)
		map->table[hash_index] = elem->next;
	else
		prev->next = elem->next;
	if (map->destroy_value)
		map->destroy_value(elem->value);
	free(elem->key);
	free(elem);
	map->elem_count--;
}
