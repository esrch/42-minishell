#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include <stdbool.h>

# include "token_list.h"

t_token_list	*tl_scanner_advance(t_token_list **token_list);
t_token_type	tl_scanner_peek_type(t_token_list **token_list);
bool			tl_scanner_check_type(t_token_list **token_list, t_token_type type);
bool			tl_scanner_match_type(t_token_list **token_list, t_token_type type);
bool			tl_scanner_is_at_end(t_token_list **token_list);

#endif