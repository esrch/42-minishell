#include "exec.h"
#include "exec_internal.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "word_list.h"
#include "ft_error.h"

static int	exec_single_cmd(t_ast_node *node)
{
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	if (child_pid == 0)
		exec_cmd(node);
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	else
		return (2);
}

void	exec_ast(t_ast_node *ast)
{
	(void) ast;

	if (ast->type == AST_CMD)
		exec_single_cmd(ast);
	else
		ft_printf("Not yet implemented\n");
}