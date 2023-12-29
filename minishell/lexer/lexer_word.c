#include "lexer.h"

static int	consume_double_quote_string(t_char_lexer *lexer);
static int	consume_single_quote_string(t_char_lexer *lexer);

int	scan_word_token(t_char_lexer *lexer, t_token_list **token_list)
{
	char	*lexeme;

	while (!char_lexer_is_at_end(lexer) && !lexer_is_metacharacter(char_lexer_peek(lexer)))
	{
		if (char_lexer_match(lexer, "\""))
		{
			if (consume_double_quote_string(lexer) < 0)
				return (-1);
		}
		else if (char_lexer_match(lexer, "'"))
		{
			if (consume_single_quote_string(lexer) < 0)
				return (-1);
		}
		else
			char_lexer_advance(lexer);
	}
	lexeme = char_lexer_extract(lexer);
	if (!lexeme)
	{
		printf("Error adding lexeme.\n");
		return (-1);
	}
	return (token_list_add_word(token_list, lexeme, NULL));
}

static int	consume_double_quote_string(t_char_lexer *lexer)
{
	char_lexer_advance_delim(lexer, "\"");
	if (char_lexer_match(lexer, "\""))
		return (0);
	printf("Error: Missing ending double quote.\n");
	return (-1);
}

static int	consume_single_quote_string(t_char_lexer *lexer)
{
	char_lexer_advance_delim(lexer, "\'");
	if (char_lexer_match(lexer, "\'"))
		return (0);
	printf("Error: Missing ending single quote.\n");
	return (-1);
}