#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "ft_error.h"
# include "token_list.h"

t_token_list	*tokenize(char *cmd, t_error *error);

#endif