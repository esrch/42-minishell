#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include <stdio.h>

# include "../char_lexer/char_lexer.h"
# include "../token/token.h"

// Lexer.
t_token_list	*lexer_scan(char *source);

// Lexer word.
int				scan_word_token(t_char_lexer *lexer, t_token_list **token_list);

// Lexer utils.
bool			lexer_is_whitespace(char c);
bool			lexer_is_metacharacter(char c);
t_token_list	*lexer_error(t_token_list *token_list, char *msg);

#endif /* LEXER_H */