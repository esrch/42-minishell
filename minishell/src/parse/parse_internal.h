#ifndef PARSE_INTERNAL_H
# define PARSE_INTERNAL_H

# include "ast.h"
# include "ft_error.h"
# include "tl_scanner.h"

t_ast_node	*parse_and_or(t_tl_scanner *scanner, t_error *error);
t_ast_node	*parse_pipeline(t_tl_scanner *scanner, t_error *error);
t_ast_node	*parse_full_cmd(t_tl_scanner *scanner, t_error *error);

#endif