#ifndef PARSE_H
# define PARSE_H

# include "ast.h"
# include "ft_error.h"
# include "token_list.h"

t_ast_node	*parse(t_token_list	*token_list, t_error *error);

#endif