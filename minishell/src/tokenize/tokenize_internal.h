#ifndef TOKENIZE_INTERNAL_H
# define TOKENIZE_INTERNAL_H

# include "ft_error.h"
# include "scanner.h"
# include "token.h"

# define TOKENIZE_WHITESPACE " \t\n"
# define TOKENIZE_METACHARACTERS " \t\n<>|&;()"

t_token	*next_token(t_scanner *scanner, t_error *error);
t_token	*next_op_token(t_scanner *scanner, t_error *error);
t_token	*next_word_token(t_scanner *scanner, t_error *error);

#endif