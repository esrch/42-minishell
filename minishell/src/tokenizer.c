#include "../includes/minishell.h"

static int	scan_token(t_char_tokenizer *tokenizer, t_token_list **token_list);
static int	scan_non_op_token(t_char_tokenizer *tokenizer, t_token_list **token_list);

t_token_list	*tokenize(char *source)
{
	t_char_tokenizer	tokenizer;
	t_token_list	*token_list;

	char_tokenizer_init(&tokenizer, source);
	token_list = NULL;
	while (!char_tokenizer_is_at_end(&tokenizer))
	{
		tokenizer.start = tokenizer.current;
		if (scan_token(&tokenizer, &token_list) < 0)
			return (tokenizer_error(token_list, NULL));
	}
	if (token_list_add_token_type(&token_list, T_EOF) < 0)
		return (tokenizer_error(token_list, "Error adding EOF.\n"));
	return (token_list);
}

static int	scan_token(t_char_tokenizer *tokenizer, t_token_list **token_list)
{
	if (char_tokenizer_match(tokenizer, "&&"))
		return (token_list_add_token_type(token_list, T_AND_AND));
	if (char_tokenizer_match(tokenizer, "||"))
		return (token_list_add_token_type(token_list, T_PIPE_PIPE));
	if (char_tokenizer_match(tokenizer, "|"))
		return (token_list_add_token_type(token_list, T_PIPE));
	if (char_tokenizer_match(tokenizer, "<<"))
		return (token_list_add_token_type(token_list, T_LESS_LESS));
	if (char_tokenizer_match(tokenizer, "<"))
		return (token_list_add_token_type(token_list, T_LESS));
	if (char_tokenizer_match(tokenizer, ">>"))
		return (token_list_add_token_type(token_list, T_GREAT_GREAT));
	if (char_tokenizer_match(tokenizer, ">"))
		return (token_list_add_token_type(token_list, T_GREAT));
	if (char_tokenizer_match(tokenizer, "("))
		return (token_list_add_token_type(token_list, T_PAREN_OPEN));
	if (char_tokenizer_match(tokenizer, ")"))
		return (token_list_add_token_type(token_list, T_PAREN_CLOSE));
	return (scan_non_op_token(tokenizer, token_list));
}

static int	scan_non_op_token(t_char_tokenizer *tokenizer, t_token_list **token_list)
{
	char	c;

	c = char_tokenizer_peek(tokenizer);
	if (tokenizer_is_whitespace(c))
	{
		char_tokenizer_advance(tokenizer);
		return (0);
	}
	if (tokenizer_is_metacharacter(c))
	{
		printf("Syntax error near '%c'.\n", c);
		return (-1);
	}
	return (tokenize_word(tokenizer, token_list));
}
