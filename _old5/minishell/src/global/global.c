#include "global.h"
#include "global_internal.h"

#include "ast.h"
#include "env.h"

/** Returns the address of the global structure
 * 
*/
static t_global	*get_global(void)
{
	static t_global	global;

	return (&global);
}

/** Initializes the global program name based on the value of argv[0].
 * 
 * If argv[0] contains a slash, the name is the string after the last slash.
 * Otherwise, the name is the full argv[0].
*/
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

/** Returns the value of the global program name
 * 
*/
char	*global_get_prog_name(void)
{
	return (get_global()->prog_name);
}

/** Updates the global AST
 * 
*/
void	global_set_ast(t_ast_node *ast)
{
	t_global	*global;

	global = get_global();
	if (global->ast)
		ast_destroy(global->ast);
	global->ast = ast;
}

/** Cleans up the global data, as well as the environment
 * 
*/
void	global_cleanup(void)
{
	t_global	*global;

	global = get_global();
	if (global->ast)
		ast_destroy(global->ast);
}
