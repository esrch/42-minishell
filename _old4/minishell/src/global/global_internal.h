#ifndef GLOBAL_INTERNAL_H
# define GLOBAL_INTERNAL_H

# include "global.h"

# include "ast.h"

typedef struct s_global
{
	char		*prog_name;
	t_ast_node	*ast;
}	t_global;

#endif