#ifndef GLOBAL_H
# define GLOBAL_H

# include "ast.h"

void	global_clean(void);
void	global_set_program_name(char *argv0);
char	*global_get_program_name(void);
void	global_set_ast(t_ast_node *ast);

#endif