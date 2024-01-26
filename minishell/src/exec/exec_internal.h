#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include <stdbool.h>
# include <unistd.h>
# include "ast.h"

typedef struct s_pid_list
{
	struct s_pid_list	*next;
	pid_t				pid;
}	t_pid_list;

int		exec_single_cmd(t_ast_node *node);
void	exec_cmd(t_ast_node *cmd_node);
int		exec_pipeline(t_ast_node *node);
int		exec_group(t_ast_node *node, bool is_top_level);
int		exec_and(t_ast_node *node);
int		exec_or(t_ast_node *node);

// PID list
t_pid_list	*pid_list_last(t_pid_list *list);
int			pid_list_add(t_pid_list **list, pid_t pid);
void		pid_list_destroy(t_pid_list *list);

#endif