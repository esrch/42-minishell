#include "hash_map.h"
#include "hash_map_internal.h"
#include "libft.h"

/** Returns an optimal table size given a minimum size.
 * 
 * To optimize distribution, a hash table size should be be a prime number.
 * 
 * Returns a table size greater or equal to the given min_size.
*/
size_t	hash_map_table_size(size_t min_size)
{
	static size_t	primes[] = {
		23UL, 47UL, 97UL, 197UL, 397UL, 797UL, 1597UL, 3203UL, 6421UL, 12853UL,
		25717UL, 51437UL, 102877UL, 205759UL, 411527UL, 823117UL, 1646237UL,
		3292489UL, 6584983UL, 13169977UL, 26339969UL, 52679969UL, 105359939UL};
	size_t			i;

	i = 0;
	if (min_size <= 23UL)
		return (23UL);
	if (min_size >= 105359939UL)
		return (105359939UL);
	while (min_size >= primes[i])
		i++;
	return (primes[i - 1]);
}

/** Returns the hash index for a given key, constrained to the given table size.
 * 
*/
size_t	hash_map_hash_index(size_t table_size, char *key)
{
	size_t			hash;
	static size_t	g = 31;

	hash = 0;
	while (*key)
	{
		hash = g * hash + *key; 
		key++;
	}
	return (hash % table_size);
}

/** Moves all elements of a linked list to a new table after recalculating
 * the hash for each element.
 * 
 * Used internally by hash_map_resize.
*/
static void	hash_map_move(t_hash_elem *head, t_hash_elem **new_table,
	size_t new_size)
{
	t_hash_elem	*next_elem;
	size_t		hash_index;

	while (head)
	{
		next_elem = head->next;
		hash_index = hash_map_hash_index(new_size, head->key);
		head->next = new_table[hash_index];
		new_table[hash_index] = head;
		head = next_elem;
	}
}

/** Resizes the hash table.
 * 
 * Used internally to keep the load factor within MAX_LOAD_FACTOR range.
 * The new size is the next prime number after doubling the current size.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	hash_map_resize(t_hash_map *map)
{
	t_hash_elem	**new_table;
	size_t		new_size;
	size_t		i;

	new_size = hash_map_table_size(map->table_size + 1);
	if (new_size == map->table_size)
		return (0);
	new_table = ft_calloc(new_size, sizeof(t_hash_elem *));
	if (!new_table)
		return (-1);
	i = 0;
	while (i < map->table_size)
	{
		hash_map_move(map->table[i], new_table, new_size);
		i++;
	}
	free(map->table);
	map->table = new_table;
	map->table_size = new_size;
	return (0);
}
