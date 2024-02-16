#ifndef GLOBAL_H
# define GLOBAL_H

# include "ast.h"

void	global_prog_name_init(char *argv0);
char	global_prog_name_get(void);
void	global_ast_set(t_ast_node *ast);
void	global_cleanup(void);

#endif