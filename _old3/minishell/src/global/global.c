#include "global.h"
#include "global_internal.h"

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "ast.h"

static t_global	*get_global()
{
	static t_global	global;

	return (&global);
}

void	global_set_program_name(char *argv0)
{
	int			i;
	int			last_slash_pos;
	t_global	*global;

	last_slash_pos = -1;
	i = 0;
	while (argv0[i])
	{
		if (argv0[i] == '/')
			last_slash_pos = i;
		i++;
	}
	global = get_global();
	global->program_name = argv0 + (last_slash_pos + 1);
}

char	*global_get_program_name(void)
{
	return (get_global()->program_name);
}

void	global_set_ast(t_ast_node *ast)
{
	t_global	*global;
	
	global = get_global();
	if (global->ast)
		ast_node_destroy(global->ast);
	global->ast = ast;
}

void	global_clean(void)
{
	t_global	*global;

	global = get_global();
	ast_node_destroy(global->ast);
}