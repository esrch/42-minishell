#include "tokenizer.h"

#include <stdlib.h>
#include "libft.h"
#include "defines.h"
#include "token_list.h"
#include "ft_error.h"
#include "char_scanner.h"
#include "ft_sprintf_malloc.h"

static bool	is_whitespace(char c)
{
	return ft_strchr(WHITESPACE, c) != NULL;
}

static bool	is_metacharacter(char c)
{
	return ft_strchr(METACHARACTERS, c) != NULL;
}

static void	skip_whitespace(t_char_scanner *scanner)
{
	char_scanner_advance_while(scanner, WHITESPACE);
}

static t_status	tokenize_op(t_char_scanner *scanner,
	t_token_list **token_list)
{
	if (char_scanner_match(scanner, "&&"))
		return (token_list_add_op(token_list, T_AND_AND));
	else if (char_scanner_match(scanner, "||"))
		return (token_list_add_op(token_list, T_PIPE_PIPE));
	else if (char_scanner_match(scanner, "|"))
		return (token_list_add_op(token_list, T_PIPE));
	else if (char_scanner_match(scanner, "<<"))
		return (token_list_add_op(token_list, T_LESS_LESS));
	else if (char_scanner_match(scanner, "<"))
		return (token_list_add_op(token_list, T_LESS));
	else if (char_scanner_match(scanner, ">>"))
		return (token_list_add_op(token_list, T_GREAT_GREAT));
	else if (char_scanner_match(scanner, ">"))
		return (token_list_add_op(token_list, T_GREAT));
	else if (char_scanner_match(scanner, "("))
		return (token_list_add_op(token_list, T_PAREN_OPEN));
	else if (char_scanner_match(scanner, ")"))
		return (token_list_add_op(token_list, T_PAREN_CLOSE));
	else
	{
		error_print_custom(ft_sprintf_malloc(
			"syntax error near unexpected '%c'", char_scanner_peek(scanner)));
		return (STATUS_ERROR);
	}
}

static t_status	handle_single_quote(t_char_scanner *scanner)
{
	char_scanner_advance(scanner);
	char_scanner_advance_until(scanner, "'");
	if (!char_scanner_match(scanner, "'"))
	{
		error_print_custom(ft_strdup("syntax error: Missing closing single quote."));
		return (STATUS_ERROR);
	}
	return (STATUS_OK);
}

static t_status	handle_double_quote(t_char_scanner *scanner)
{
	char_scanner_advance(scanner);
	char_scanner_advance_until(scanner, "\"");
	if (!char_scanner_match(scanner, "\""))
	{
		error_print_custom(ft_strdup("syntax error: Missing closing double quote."));
		return (STATUS_ERROR);
	}
	return (STATUS_OK);
}

static t_status	tokenize_word(t_char_scanner *scanner, t_token_list **token_list)
{
	t_status	status;
	char		next_char;
	char		*extracted;

	status = STATUS_OK;
	next_char = char_scanner_peek(scanner);
	while (!char_scanner_is_at_end(scanner) && !is_metacharacter(next_char))
	{
		if (next_char == '\'')
			status = handle_single_quote(scanner);
		else if (next_char == '"')
			status = handle_double_quote(scanner);
		else
			status = char_scanner_advance(scanner);
		if (status == STATUS_ERROR)
			return (STATUS_ERROR);
		next_char = char_scanner_peek(scanner);
	}
	extracted = char_scanner_extract(scanner);
	if (!extracted)
		return (STATUS_ERROR);
	if (token_list_add_word(token_list, extracted) == STATUS_ERROR)
	{
		free(extracted);
		return (STATUS_ERROR);
	}
	return (STATUS_OK);
}

static t_status	tokenize_next(t_char_scanner *scanner, t_token_list **token_list)
{
	t_status	status;
	char		next_char;

	next_char = char_scanner_peek(scanner);

	status = STATUS_OK;
	if (is_whitespace(next_char))
		skip_whitespace(scanner);
	else if (is_metacharacter(next_char))
		status = tokenize_op(scanner, token_list);
	else
		status = tokenize_word(scanner, token_list);
	return (status);
}

t_token_list	*tokenize(char *src)
{
	t_char_scanner	scanner;
	t_token_list	*token_list;

	char_scanner_init(&scanner, src);
	token_list = NULL;
	while (!char_scanner_is_at_end(&scanner))
	{
		if (tokenize_next(&scanner, &token_list) == STATUS_ERROR)
		{
			token_list_clear(token_list);
			return (NULL);
		}
		char_scanner_sync_start(&scanner);
	}
	if (token_list_add_op(&token_list, T_EOF) == STATUS_ERROR)
	{
		token_list_clear(token_list);
		return (NULL);
	}
	return (token_list);
}
