#ifndef CHAR_TOKENIZER_H
# define CHAR_TOKENIZER_H

# include <stdbool.h>

typedef struct s_char_tokenizer
{
	char	*src;
	int		start;
	int		current;
}	t_char_tokenizer;

// Char tokenizer.
void			char_tokenizer_init(t_char_tokenizer *tokenizer, char *src);
t_char_tokenizer	*char_tokenizer_construct(char *src);
void			char_tokenizer_destruct(t_char_tokenizer *tokenizer);
char			*char_tokenizer_extract(t_char_tokenizer *tokenizer);

bool			char_tokenizer_is_at_end(t_char_tokenizer *tokenizer);
char			char_tokenizer_advance(t_char_tokenizer *tokenizer);
int				char_tokenizer_advance_delim(t_char_tokenizer *tokenizer, char *delim);
int				char_tokenizer_advance_while(t_char_tokenizer *tokenizer,
					bool (*predicate)(char c));
char			char_tokenizer_peek(t_char_tokenizer *tokenizer);
char			char_tokenizer_previous(t_char_tokenizer *tokenizer);
bool			char_tokenizer_match(t_char_tokenizer *tokenizer, char *expected);

#endif /* CHAR_TOKENIZER_H */