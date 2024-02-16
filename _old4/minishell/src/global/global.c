#include "global.h"
#include "global_internal.h"

#include "ast.h"
#include "env.h"

static t_global	*get_global(void)
{
	static t_global	global;

	return (&global);
}

void	global_cleanup(void)
{
	t_global	*global;

	global = get_global();
	if (global->ast)
		ast_destroy(global->ast);
	env_destroy();
}

void	global_init_prog_name(char *argv0)
{
	int	i;
	int	last_slash_pos;

	last_slash_pos = -1;
	i = 0;
	while (argv0[i])
	{
		if (argv0[i] == '/')
			last_slash_pos = i;
		i++;
	}
	get_global()->prog_name = argv0 + last_slash_pos + 1;
}

char	*global_get_prog_name(void)
{
	return (get_global()->prog_name);
}

void	global_set_ast(t_ast_node *ast)
{
	t_global	*global;

	global = get_global();
	if (global->ast)
		ast_destroy(global->ast);
	global->ast = ast;
}
