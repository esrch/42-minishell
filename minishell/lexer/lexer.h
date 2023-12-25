#ifndef LEXEME_H
# define LEXEME_H

# include <stdbool.h>
# include <stdio.h>

# include "../token/token.h"

typedef struct s_lexer
{
	char			*source;
	int				start;
	int				current;
	t_token_list	*token_list;
}	t_lexer;

// Lexer.
t_token_list	*lexer_scan(char *source);

// Lexer word.
int				scan_word(t_lexer *lexer);

// Lexer utils.
bool			lexer_is_at_end(t_lexer *lexer);
char			lexer_advance(t_lexer *lexer);
char			lexer_peek(t_lexer *lexer);
bool			lexer_match(t_lexer *lexer, char expected);
bool			lexer_is_whitespace(char c);
bool			lexer_is_metacharacter(char c);
t_token_list	*lexer_error(t_lexer *lexer);
char			*lexer_extract_lexeme(t_lexer *lexer);

#endif /* LEXEME_H */