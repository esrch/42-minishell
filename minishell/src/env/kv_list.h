#ifndef KV_LIST_H
# define KV_LIST_H

# include <stdbool.h>

typedef struct s_kv_list
{
	struct s_kv_list	*next;
	char				*key;
	char				*value;
}	t_kv_list;

int		kv_list_add(t_kv_list **list, char *key, char *value);
int		kv_list_update(t_kv_list *node, char *value);
void	kv_list_destroy(t_kv_list *list);
int		kv_list_len(t_kv_list *list);

#endif