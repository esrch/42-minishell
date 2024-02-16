#include "exec_internal.h"

#include <stdlib.h>
#include <unistd.h>

#include "ft_error.h"

void	pid_list_add(t_pid_list **list, pid_t pid, t_error *error)
{
	t_pid_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node)
	{
		new_node->next = NULL;
		new_node->pid = pid;
	}
	else
		error_set_system(error);
	if (!*list)
		*list = new_node;
	else
		pid_list_last(*list)->next = new_node;
}

void	pid_list_destroy(t_pid_list *list)
{
	t_pid_list	*next_node;

	while (list)
	{
		next_node = list->next;
		free(list);
		list = next_node;
	}
}

t_pid_list	*pid_list_last(t_pid_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}
