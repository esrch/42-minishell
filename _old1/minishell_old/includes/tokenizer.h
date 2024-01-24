#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdbool.h>

# include "token_list.h"

// Tokenizer.
t_token_list	*tokenize(char *source);

// Tokenizer word.
int				tokenize_word(t_char_tokenizer *tokenizer, t_token_list **token_list);

// Tokenizer utils.
bool			tokenizer_is_whitespace(char c);
bool			tokenizer_is_metacharacter(char c);
t_token_list	*tokenizer_error(t_token_list *token_list, char *msg);

#endif /* TOKENIZER_H */