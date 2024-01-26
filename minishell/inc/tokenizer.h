#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "ft_error.h"
# include "token_list.h"

#define WHITESPACE " \t\n"
#define METACHARACTERS " \t\n<>|&;()"

t_token_list	*tokenize(char *src);

#endif /* TOKENIZER_H */