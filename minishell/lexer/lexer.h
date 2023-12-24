#ifndef LEXEME_H
# define LEXEME_H

# include <stdbool.h>

# include "../token/token.h"

typedef struct s_lexer
{
	char			*source;
	int				start;
	int				current;
	t_token_list	*token_list;
}	t_lexer;

// Lexer.
void	lexer_init(t_lexer *lexer, char *source);

// Lexer utils.
bool	is_at_end(t_lexer *lexer);
char	advance(t_lexer *lexer);
char	peek(t_lexer *lexer);
bool	match(t_lexer *lexer, char expected);

#endif /* LEXEME_H */