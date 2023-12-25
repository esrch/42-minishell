#ifndef CHAR_LEXER_H
# define CHAR_LEXER_H

# include <stdbool.h>
# include <stdlib.h>

typedef struct s_char_lexer
{
	char	*src;
	int		start;
	int		current;
}	t_char_lexer;

// Char lexer.
void			char_lexer_init(t_char_lexer *lexer, char *src);
t_char_lexer	*char_lexer_construct(char *src);
void			char_lexer_destruct(t_char_lexer *lexer);
char			*char_lexer_extract(t_char_lexer *lexer);

bool			char_lexer_is_at_end(t_char_lexer *lexer);
char			char_lexer_advance(t_char_lexer *lexer);
int				char_lexer_advance_delim(t_char_lexer *lexer, char *delim);
int				char_lexer_advance_while(t_char_lexer *lexer,
					bool (*predicate)(char c));
char			char_lexer_peek(t_char_lexer *lexer);
char			char_lexer_previous(t_char_lexer *lexer);
bool			char_lexer_match(t_char_lexer *lexer, char *expected);

#endif /* CHAR_LEXER_H */