#include "exec_internal.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "ft_error.h"

/** Adds a pid to the list.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	pid_list_add(t_pid_list **list, pid_t pid)
{
	t_pid_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node)
	{
		new_node->next = NULL;
		new_node->pid = pid;
	}
	else
	 	return (-1);
	if (!*list)
		*list = new_node;
	else
		pid_list_last(*list)->next = new_node;
	return (0);
}

/** Frees the allocated memory for the list.
 * 
*/
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

/** Returns the last element of the pid list, or NULL if it is empty.
 * 
*/
t_pid_list	*pid_list_last(t_pid_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/** Wait for the processes listed in pid_list to finish.
 * 
 * Returns the exit code of the last process in the list.
*/
int	pid_list_wait(t_pid_list *pid_list)
{
	int		status;
	int		exit_status;
	pid_t	pid;
	pid_t	last_pid;

	exit_status = 0;
	last_pid = pid_list_last(pid_list)->pid;
	while (pid_list)
	{
		pid = waitpid(0, &status, 0);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = WTERMSIG(status);
		}
		pid_list = pid_list->next;
	}
	return (exit_status);
}