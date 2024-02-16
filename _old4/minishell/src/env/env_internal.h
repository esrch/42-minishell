#ifndef ENV_INTERNAL_H
# define ENV_INTERNAL_H

# include "ft_error.h"

typedef struct s_env_list
{
	struct s_env_list	*next;
	char				*key;
	char				*value;
}	t_env_list;

void		env_list_add(t_env_list **list, char *key, char *value, t_error *error);
void		env_list_update_node(t_env_list *node, char *value, t_error *error);
t_env_list	*env_list_find(t_env_list *list, char *key);
void		env_list_destroy_node(t_env_list *node);
void		env_list_destroy(t_env_list *list);
void		env_list_remove_node(t_env_list **node);
int			env_list_len(t_env_list *list);

#endif