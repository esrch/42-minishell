#include "lexer.h"

static int	scan_token(t_lexer *lexer);

static void	lexer_init(t_lexer *lexer, char *source)
{
	lexer->source = source;
	lexer->start = 0;
	lexer->current = 0;
	lexer->token_list = NULL;
}

t_token_list	*lexer_scan(char *source)
{
	t_lexer	lexer;

	lexer_init(&lexer, source);
	while (!lexer_is_at_end(&lexer))
	{
		lexer.start = lexer.current;
		if (scan_token(&lexer) < 0)
			return (lexer_error(&lexer));
	}
	if (token_list_add_token_type(&lexer.token_list, T_EOF) < 0)
	{
		printf("Error adding EOF.\n");
		return (lexer_error(&lexer));
	}
	return (lexer.token_list);
}

static int	scan_token(t_lexer *lexer)
{
	char	c;

	c = lexer_advance(lexer);
	if (c == '&' && lexer_match(lexer, '&'))
		return (token_list_add_token_type(&lexer->token_list, T_AND_AND));
	if (c == '|' && lexer_match(lexer, '|'))
		return (token_list_add_token_type(&lexer->token_list, T_PIPE_PIPE));
	if (c == '|')
		return (token_list_add_token_type(&lexer->token_list, T_PIPE_PIPE));
	if (c == '<' && lexer_match(lexer, '<'))
		return (token_list_add_token_type(&lexer->token_list, T_LESS_LESS));
	if (c == '<')
		return (token_list_add_token_type(&lexer->token_list, T_LESS));
	if (c == '>' && lexer_match(lexer, '>'))
		return (token_list_add_token_type(&lexer->token_list, T_GREAT_GREAT));
	if (c == '>')
		return (token_list_add_token_type(&lexer->token_list, T_GREAT));
	if (c == '(')
		return (token_list_add_token_type(&lexer->token_list, T_PAREN_OPEN));
	if (c == ')')
		return (token_list_add_token_type(&lexer->token_list, T_PAREN_CLOSE));
	if (lexer_is_whitespace(c))
		return (0);
	if (lexer_is_metacharacter(c))
	{
		printf("Syntax error near '%c'.\n", c);
		return (-1);
	}
	return (scan_word(lexer));
}
