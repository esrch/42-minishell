#include "lexer.h"

static int	consume_word(t_lexer *lexer);
static int	consume_single_quote_string(t_lexer *lexer);
static int	consume_double_quote_string(t_lexer *lexer);

int	scan_word(t_lexer *lexer)
{
	char	*lexeme;

	if (consume_word(lexer) < 0)
		return (-1);
	lexeme = lexer_extract_lexeme(lexer);
	if (!lexeme)
	{
		printf("Error extracting lexeme.\n");
		return (-1);
	}
	return (token_list_add_word(&lexer->token_list, lexeme));
}

static int	consume_word(t_lexer *lexer)
{
	char	c;

	c = lexer->source[lexer->start];
	while (1)
	{
		if (c == '"' && consume_double_quote_string(lexer) < 0)
			return (-1);
		if (c == '\'' && consume_single_quote_string(lexer) < 0)
			return (-1);
		if (lexer_is_at_end(lexer))
			break ;
		if (lexer_is_metacharacter(lexer_peek(lexer)))
			break ;
		c = lexer_advance(lexer);
	}
	return (0);
}

static int	consume_double_quote_string(t_lexer *lexer)
{
	char	c;

	c = lexer_advance(lexer);
	while (c != '"' && !lexer_is_at_end(lexer))
		c = lexer_advance(lexer);
	if (c != '"')
	{
		printf("Error: Missing ending double quote.\n");
		return (-1);
	}
	return (0);
}

static int	consume_single_quote_string(t_lexer *lexer)
{
	char	c;

	c = lexer_advance(lexer);
	while (c != '\'' && !lexer_is_at_end(lexer))
		c = lexer_advance(lexer);
	if (c != '\'')
	{
		printf("Error: Missing ending single quote.\n");
		return (-1);
	}
	return (0);
}
