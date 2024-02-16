#include "env.h"

#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_error.h"

static t_kv_list	*create_node(char *key, char *value)
{
	t_kv_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
	{
		error_print_system();
		return (NULL);
	}
	new_node->next = NULL;
	new_node->key = key;
	new_node->value = value;
	return (new_node);
}

static void	destroy_node(t_kv_list *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static t_kv_list	**find_node(t_kv_list **list, char *key)
{
	t_kv_list	**current;

	current = list;
	while (*current)
	{
		if (ft_strncmp((*current)->key, key, ft_strlen(key) + 1) == 0)
			return (current);
		current = &(*current)->next;
	}
	return (NULL);
}

static t_kv_list	*last_node(t_kv_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

static t_status	add_node(t_kv_list **list, char *key, char *value)
{
	t_kv_list	*new_node;

	new_node = create_node(key, value);
	if (!new_node)
		return (STATUS_ERROR);
	if (!*list)
		*list = new_node;
	else
		last_node(*list)->next = new_node;
	return (STATUS_OK);
}

static bool	update_node(t_kv_list *list, char *key, char *value)
{
	t_kv_list	**found;

	found = find_node(&list, key);
	if (!found)
		return (false);
	free((*found)->value);
	(*found)->value = value;
	return (true);
}

static t_status	add_envp_entry(t_kv_list **env, char *envp_entry)
{
	char		*eq_pos;
	char		*key;
	char		*value;

	eq_pos = ft_strchr(envp_entry, '=');
	if (!eq_pos)
		return (STATUS_OK);
	*eq_pos = '\0';
	key = ft_strdup(envp_entry);
	value = ft_strdup(eq_pos + 1);
	*eq_pos = '=';
	if (!key || !value)
	{
		free(key);
		free(value);
		error_print_system();
		return (STATUS_ERROR);
	}
	if (add_node(env, key, value) == STATUS_ERROR)
	{
		free(key);
		free(value);
		return (STATUS_ERROR);
	}
	return (STATUS_OK);
}

t_kv_list	*env_create(char **envp)
{
	t_kv_list	*env;

	env = NULL;
	while (*envp)
	{
		if (add_envp_entry(&env, *envp) == STATUS_ERROR)
		{
			env_destroy(env);
			return (NULL);
		}
		envp++;
	}
	return (env);
}

void	env_destroy(t_kv_list *list)
{
	t_kv_list	*next;

	while (list)
	{
		next = list->next;
		destroy_node(list);
		list = next;
	}
}

t_status	env_set(t_kv_list **list, char *key, char *value)
{
	char		*key_cpy;

	if (!list || !key)
		return (STATUS_OK);
	if (update_node(*list, key, value))
		return (STATUS_OK);
	key_cpy = ft_strdup(key);
	if (!key_cpy)
	{
		error_print_system();
		return (STATUS_ERROR);
	}
	if (add_node(list, key_cpy, value) == STATUS_ERROR)
	{
		free(key_cpy);
		return (STATUS_ERROR);
	}
	return (STATUS_OK);
}

void	env_unset(t_kv_list **list, char *key)
{
	t_kv_list	**found;
	t_kv_list	*next;

	if (!list || !*list || !key)
		return ;
	found = find_node(list, key);
	if (!found)
		return ;
	next = (*found)->next;
	destroy_node(*found);
	*found = next;
}

char	*env_get(t_kv_list *list, char *key)
{
	t_kv_list	**found;
	char		*value_cpy;

	found = find_node(&list, key);
	if (!found)
		return (NULL);
	value_cpy = ft_strdup((*found)->value);
	if (!value_cpy)
	{
		error_print_system();
		return (NULL);
	}
	return (value_cpy);
}