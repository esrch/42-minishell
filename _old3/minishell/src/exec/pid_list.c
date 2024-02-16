#include "exec_internal.h"

#include <stdlib.h>
#include <unistd.h>

t_pid_list	*pid_list_last(t_pid_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	pid_list_add(t_pid_list **list, pid_t pid)
{
	t_pid_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (-1);
	new_node->next = NULL;
	new_node->pid = pid;
	if (!*list)
		*list = new_node;
	else
		pid_list_last(*list)->next = new_node;
	return (0);
}

void	pid_list_destroy(t_pid_list *list)
{
	t_pid_list	*next;
	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}