#ifndef HASH_MAP_INTERNAL_H
# define HASH_MAP_INTERNAL_H

# include <stdlib.h>

# include "hash_map.h"

typedef struct s_hash_elem
{
	char				*key;
	void				*value;
	struct s_hash_elem	*next;
}	t_hash_elem;

struct s_hash_map
{
	size_t						table_size;
	size_t						elem_count;
	t_hash_map_destroy_value_f	destroy_value;
	t_hash_elem					**table;
};

// Utils.
size_t	hash_map_table_size(size_t size);
size_t	hash_map_hash_index(size_t table_size, char *key);
int		hash_map_resize(t_hash_map *map);

#endif