#ifndef EXPAND_INTERNAL_H
# define EXPAND_INTERNAL_H

# include "scanner.h"
# include "word_list.h"

# define LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
# define NUMBERS "0123456789"

// Expand params
char		*expand_params(char *word);
int			extract_segment(t_scanner *scanner, t_word_list **segments);
int			add_param(char *param_name, t_word_list **segments);
int			handle_param(t_scanner *scanner, t_word_list **segments);

// Split words
t_word_list	*split_words(char *str);

// Expand wildcard
t_word_list	*expand_wildcard(t_word_list *argv);

// Unquote words
void	expand_unquote(t_word_list *argv);

#endif