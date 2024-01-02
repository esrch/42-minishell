#include "_minishell.h"

static int	scan_token(t_lexer *lexer, t_token_list **token_list);

static t_token_list	*cleanup_error(t_token_list **token_list)
{
	token_list_clear(token_list);
	return (NULL);
}

t_token_list	*ms_tokenize(char *src){
	t_lexer			lexer;
	t_token_list	*token_list;

	lexer_init(&lexer, src);
	token_list = NULL;
	while (!lexer_at_end(&lexer))
	{
		lexer.start = lexer.current;
		if (scan_token(&lexer, &token_list) < 0)
			return (cleanup_error(&token_list));
	}
	if (token_list_add_op(&token_list, T_EOF) < 0)
		return (cleanup_error(&token_list));
	return (token_list);
}

static int	tokenize_op(t_lexer *lexer, t_token_list **token_list)
{
	if (lexer_match(lexer, "&&"))
		return (token_list_add_op(token_list, T_AND_AND));
	if (lexer_match(lexer, "||"))
		return (token_list_add_op(token_list, T_PIPE_PIPE));
	if (lexer_match(lexer, "|"))
		return (token_list_add_op(token_list, T_PIPE));
	if (lexer_match(lexer, ">>"))
		return (token_list_add_op(token_list, T_GREAT_GREAT));
	if (lexer_match(lexer, ">"))
		return (token_list_add_op(token_list, T_GREAT));
	if (lexer_match(lexer, "<<"))
		return (token_list_add_op(token_list, T_LESS_LESS));
	if (lexer_match(lexer, "<"))
		return (token_list_add_op(token_list, T_LESS));
	if (lexer_match(lexer, "("))
		return (token_list_add_op(token_list, T_PAREN_OPEN));
	if (lexer_match(lexer, ")"))
		return (token_list_add_op(token_list, T_PAREN_CLOSE));
	ft_printf_error("Invalid character near %c\n", lexer_peek(lexer));
	return (-1);
}

static int	scan_token(t_lexer *lexer, t_token_list **token_list)
{
	if (ms_is_whitespace(lexer_peek(lexer)))
	{
		(void)lexer_advance(lexer);
		return (0);
	}
	if (ms_is_metacharacter(lexer_peek(lexer)))
		return (tokenize_op(lexer, token_list));
	return tokenize_word(lexer, token_list);
}
