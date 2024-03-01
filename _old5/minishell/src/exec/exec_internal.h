#ifndef EXEC_INTERNAL_H
#define EXEC_INTERNAL_H

#include <unistd.h>

#include "ast.h"
#include "ft_error.h"
#include "redirection.h"

typedef struct s_pid_list {
  struct s_pid_list *next;
  pid_t pid;
}	t_pid_list;

// Exec
pid_t		exec_cmd(t_ast_node *node, int in_fd, int *out_fd);
int			exec_simple_cmd(t_ast_node *node);
pid_t		exec_subshell(t_ast_node *node, int pipe_in_fd, int *pipe_out_fd);
int			exec_simple_subshell(t_ast_node *node);
int			exec_pipeline(t_ast_node *node);
int			exec_and(t_ast_node *node);
int			exec_or(t_ast_node *node);

// Pid list
int			pid_list_add(t_pid_list **list, pid_t pid);
void		pid_list_destroy(t_pid_list *list);
t_pid_list	*pid_list_last(t_pid_list *list);
int			pid_list_wait(t_pid_list *list);

#endif