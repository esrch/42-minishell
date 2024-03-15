#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include <stdbool.h>
# include <stdlib.h>
# include <sys/wait.h>

# include "ast.h"

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

// Execution
int			exec_and(t_ast_node *and_node);
int			exec_or(t_ast_node *or_node);
int			exec_pipeline(t_ast_node *pipe_node);
int			exec_simple_subshell(t_ast_node *subshell_node);
int			exec_subshell(t_ast_node *subshell_node);
int			exec_simple_cmd(t_ast_node *cmd_node);
void		exec_cmd(t_ast_node *cmd_node);

// Execution errors
int			handle_system_error(char *word, bool should_exit);
int			handle_ambiguous_redirect(char *word, bool should_exit);
int			handle_cmd_not_found(char *word, bool should_exit);
int			handle_permission_denied(char *word, bool should_exit);

// Builtin
bool		is_builtin(char *word);
int			exec_builtin(t_ast_node *cmd_node);
int			exec_builtin_pwd(t_ast_node *cmd_node);
int			exec_builtin_cd(t_ast_node *cmd_node);
int			exec_builtin_echo(t_ast_node *cmd_node);
int			exec_builtin_env(t_ast_node *cmd_node);
int			exec_builtin_export(t_ast_node *cmd_node);
int			exec_builtin_unset(t_ast_node *cmd_node);
int			exec_builtin_exit(t_ast_node *cmd_node);

#endif