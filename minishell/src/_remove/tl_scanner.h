#ifndef TL_SCANNER_H
# define TL_SCANNER_H

# include <stdbool.h>
# include "ft_error.h"
# include "token.h"
# include "token_list.h"
# include "word_list.h"

typedef struct s_tl_scanner
{
	t_token_list	*start;
	t_token_list	*current;
}	t_tl_scanner;

void			tl_scanner_init(t_tl_scanner *scanner, t_token_list *list);
t_token_type	tl_scanner_peek_type(t_tl_scanner *scanner);
t_token			*tl_scanner_advance(t_tl_scanner *scanner);
void			tl_scanner_advance_while(t_tl_scanner *scanner, t_token_type type);
bool			tl_scanner_match_type(t_tl_scanner *scanner, t_token_type type);
bool			tl_scanner_is_at_end(t_tl_scanner *scanner);
void			tl_scanner_sync_start(t_tl_scanner *scanner);
t_word_list		*tl_scanner_extract_values(t_tl_scanner *scanner, t_error *error);

#endif /* TL_SCANNER_H */