#ifndef GLOBAL_INTERNAL_H
# define GLOBAL_INTERNAL_H

# include "ast.h"

typedef struct s_global
{
	char		*program_name;
	t_ast_node	*ast;
}	t_global;

#endif