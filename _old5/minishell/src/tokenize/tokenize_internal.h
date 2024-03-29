#ifndef TOKENIZE_INTERNAL_H
# define TOKENIZE_INTERNAL_H

# include <stdbool.h>

# include "ft_error.h"
# include "scanner.h"
# include "token_list.h"

# define WHITESPACE " \t\n"
# define METACHARACTERS " \t\n<>|&;()"

bool	is_metacharacter(char c);
void	tokenize_op(t_scanner *scanner, t_token_list **token_list,
			t_error *error);
void	tokenize_word(t_scanner *scanner, t_token_list **token_list,
			t_error *error);

#endif