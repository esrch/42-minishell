#include "_minishell.h"

static int	extract_word(t_lexer *lexer, t_token_list **token_list)
{
	char	*lexeme;

	lexeme = lexer_extract(lexer);
	if (!lexeme)
		return (-1);
	if (token_list_add_word(token_list, lexeme, NULL) < 0)
	{
		free(lexeme);
		return (-1);
	}
	return (0);
}

static int	handle_double_quote(t_lexer *lexer)
{
	lexer_advance(lexer);
	lexer_advance_delim(lexer, "\"");
	if (!lexer_match(lexer, "\""))
	{
		ft_printf_error("Missing ending double quote.\n");
		return (-1);
	}
	return (0);
}

static int	handle_single_quote(t_lexer *lexer)
{
	lexer_advance(lexer);
	lexer_advance_delim(lexer, "'");
	if (!lexer_match(lexer, "'"))
	{
		ft_printf_error("Missing ending single quote.\n");
		return (-1);
	}
	return (0);
}

int	tokenize_word(t_lexer *lexer, t_token_list **token_list)
{
	while (!lexer_at_end(lexer))
	{
		if (ms_is_metacharacter(lexer_peek(lexer)))
			break;
		if (lexer_peek(lexer) == '"')
		{
			if (handle_double_quote(lexer) < 0)
				return (-1);
		}
		else if (lexer_peek(lexer) == '\'')
		{
			if (handle_single_quote(lexer) < 0)
				return (-1);
		}
		else
			lexer_advance(lexer);
	}
	return (extract_word(lexer, token_list));
}

