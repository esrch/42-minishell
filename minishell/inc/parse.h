#ifndef PARSE_H
# define PARSE_H

# include "ast.h"
# include "ft_error.h"
# include "heredoc_list.h"
# include "token_list.h"

t_ast_node	*parse(t_token_list	*token_list, t_heredoc_list **heredocs,
				t_error *error);

#endif