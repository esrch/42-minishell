#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include "exec.h"

typedef struct s_pid_list
{
	struct s_pid_list *next;
	pid_t pid;
}	t_pid_list;

// Pid list
int			pid_list_add(t_pid_list **list, pid_t pid);
void		pid_list_destroy(t_pid_list *list);
t_pid_list	*pid_list_last(t_pid_list *list);
int			pid_list_wait(t_pid_list *list);

#endif