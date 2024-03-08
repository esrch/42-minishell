#ifndef TL_SCANNER_H
# define TL_SCANNER_H

# include <stdbool.h>

# include "ft_error.h"
# include "token_list.h"
# include "word_list.h"

typedef struct s_tl_scanner
{
	t_token_list	*current_node;
}	t_tl_scanner;

void		tl_scanner_init(t_tl_scanner *scanner, t_token_list *token_list);
bool		tl_scanner_is_at_end(t_tl_scanner *scanner);
t_token		*tl_scanner_advance(t_tl_scanner *scanner);
t_token		*tl_scanner_peek(t_tl_scanner *scanner);
bool		tl_scanner_check_type(t_tl_scanner *scanner, t_token_type type);
bool		tl_scanner_match_type(t_tl_scanner *scanner, t_token_type type);
t_word_list	*tl_scanner_extract_words(t_tl_scanner *scanner, t_error *error);

#endif