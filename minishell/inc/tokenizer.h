#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "ft_error.h"
# include "token_list.h"

#define WHITESPACE " \t\n"
#define METACHARACTERS " \t\n<>|&;()"

t_token_list	*tokenize(char *src, t_error *error);

#endif /* TOKENIZER_H */