#ifndef EXPANSION_INTERNAL_H
# define EXPANSION_INTERNAL_H

# include "../../inc/env.h"
# include "../../inc/error.h"
# include "../../inc/str_list.h"

# define LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
# define NUMBERS "0123456789"

char		*expand_params(char *token_value, t_env env, t_error *error);
t_str_list	*split_words(char *s, char *delimiters, t_error *error);

#endif