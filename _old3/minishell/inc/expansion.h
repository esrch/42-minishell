#ifndef EXPANSION_H
# define EXPANSION_H

# include "ft_error.h"
# include "env.h"
# include "token_list.h"

void	expand_words(t_token_list **token_list, t_env env, t_error *error);

#endif