#ifndef HASH_MAP_H
# define HASH_MAP_H

# include <stdbool.h>
# include <stdlib.h>

# define MAX_LOAD_FACTOR 0.75

typedef struct s_hash_map	t_hash_map;
typedef void	(*t_hash_map_destroy_value_f)(void *value);

t_hash_map	*hash_map_create(t_hash_map_destroy_value_f destroy_value);
void		hash_map_destroy(t_hash_map *map);
char		**hash_map_keys(t_hash_map *map);
size_t		hash_map_count(t_hash_map *map);
int			hash_map_set(t_hash_map *map, char *key, void *value);
void		*hash_map_get(t_hash_map *map, char *key);
void		hash_map_unset(t_hash_map *map, char *key);

#endif