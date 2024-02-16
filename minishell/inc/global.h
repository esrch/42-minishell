#ifndef GLOBAL_H
# define GLOBAL_H

# include "ast.h"

void	global_init_prog_name(char *argv0);
char	*global_get_prog_name(void);
void	global_ast_set(t_ast_node *ast);
void	global_cleanup(void);

#endif