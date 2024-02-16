#ifndef GLOBAL_H
# define GLOBAL_H

# include "ast.h"

void	global_cleanup(void);
void	global_init_prog_name(char *argv0);
char	*global_get_prog_name(void);
void	global_set_ast(t_ast_node *ast);

#endif