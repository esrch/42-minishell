#ifndef WORD_SPLIT_H
# define WORD_SPLIT_H

# include "../token/token.h"
# include "../char_lexer/char_lexer.h"

t_token_list	*split_words(t_token *token);

#endif /* WORD_SPLIT_H */