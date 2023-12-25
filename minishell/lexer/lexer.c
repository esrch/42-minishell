#include "lexer.h"

static int	scan_token(t_char_lexer *lexer, t_token_list **token_list);
static int	scan_non_op_token(t_char_lexer *lexer, t_token_list **token_list);

t_token_list	*lexer_scan(char *source)
{
	t_char_lexer	lexer;
	t_token_list	*token_list;

	char_lexer_init(&lexer, source);
	token_list = NULL;
	while (!char_lexer_is_at_end(&lexer))
	{
		lexer.start = lexer.current;
		if (scan_token(&lexer, &token_list) < 0)
			return (lexer_error(token_list, NULL));
	}
	if (token_list_add_token_type(&token_list, T_EOF) < 0)
		return (lexer_error(token_list, "Error adding EOF.\n"));
	return (token_list);
}

static int	scan_token(t_char_lexer *lexer, t_token_list **token_list)
{
	if (char_lexer_match(lexer, "&&"))
		return (token_list_add_token_type(token_list, T_AND_AND));
	if (char_lexer_match(lexer, "||"))
		return (token_list_add_token_type(token_list, T_PIPE_PIPE));
	if (char_lexer_match(lexer, "|"))
		return (token_list_add_token_type(token_list, T_PIPE));
	if (char_lexer_match(lexer, "<<"))
		return (token_list_add_token_type(token_list, T_LESS_LESS));
	if (char_lexer_match(lexer, "<"))
		return (token_list_add_token_type(token_list, T_LESS));
	if (char_lexer_match(lexer, ">>"))
		return (token_list_add_token_type(token_list, T_GREAT_GREAT));
	if (char_lexer_match(lexer, ">"))
		return (token_list_add_token_type(token_list, T_GREAT));
	if (char_lexer_match(lexer, "("))
		return (token_list_add_token_type(token_list, T_PAREN_OPEN));
	if (char_lexer_match(lexer, ")"))
		return (token_list_add_token_type(token_list, T_PAREN_CLOSE));
	return (scan_non_op_token(lexer, token_list));
}

static int	scan_non_op_token(t_char_lexer *lexer, t_token_list **token_list)
{
	char	c;

	c = char_lexer_peek(lexer);
	if (lexer_is_whitespace(c))
	{
		char_lexer_advance(lexer);
		return (0);
	}
	if (lexer_is_metacharacter(c))
	{
		printf("Syntax error near '%c'.\n", c);
		return (-1);
	}
	return (scan_word_token(lexer, token_list));
}
