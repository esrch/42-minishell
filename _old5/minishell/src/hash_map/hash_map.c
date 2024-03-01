#include "hash_map.h"
#include "hash_map_internal.h"

#include <stdlib.h>

#include "libft.h"

/** Creates a hash map.
 * 
 * destroy_value_f is a pointer to a function used to free the memory
 * of a hash map value. If NULL, values are not freed when removed.
 * 
 * Returns the map, or NULL on error.
*/
t_hash_map	*hash_map_create(t_hash_map_destroy_value_f destroy_value)
{
	t_hash_map	*map;

	map = malloc(sizeof(*map));
	if (!map)
		return (NULL);
	map->table_size = hash_map_table_size(0);
	map->elem_count = 0;
	map->destroy_value = destroy_value;
	map->table = ft_calloc(map->table_size, sizeof(t_hash_elem *));
	if (!map->table)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

/** Frees the memory for the given map
 * 
*/
void	hash_map_destroy(t_hash_map *map)
{
	size_t		i;
	t_hash_elem	*next_elem;

	i = 0;
	while (i < map->table_size)
	{
		while (map->table[i])
		{
			next_elem = map->table[i]->next;
			if (map->destroy_value)
				map->destroy_value(map->table[i]->value);
			free(map->table[i]->key);
			free(map->table[i]);
			map->table[i] = next_elem;
		}
		i++;
	}
	free(map->table);
	free(map);
}

/** Returns a NULL-terminated array of keys of the given map.
 * 
 * Returns an array of copies of keys, or NULL in case of error.
*/
char	**hash_map_keys(t_hash_map *map)
{
	char		**keys;
	size_t		table_index;
	size_t		keys_index;
	t_hash_elem	*elem;
	
	keys = ft_calloc(map->elem_count + 1, sizeof(*keys));
	if (!keys)
		return (NULL);
	table_index = 0;
	keys_index = 0;
	while (table_index < map->table_size)
	{
		elem = map->table[table_index];
		while (elem)
		{
			keys[keys_index] = ft_strdup(elem->key);
			if (!keys[keys_index])
				ft_free_2d_count((void ***) keys, keys_index);
			keys_index++;
			elem = elem->next;
		}
		table_index++;
	}
	return (keys);
}

/** Returns the number of elements in the hash map.
 * 
*/
size_t	hash_map_count(t_hash_map *map)
{
	return (map->elem_count);
}