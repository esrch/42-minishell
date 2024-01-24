#include "tokenizer.h"

#include <stdlib.h>
#include <string.h>
#include "token_list.h"
#include "ft_error.h"
#include "char_scanner.h"

static bool	is_whitespace(char c)
{
	return strchr(WHITESPACE, c) != NULL;
}

static bool	is_metacharacter(char c)
{
	// Remove dependency on <string.h>
	return strchr(METACHARACTERS, c) != NULL;
}

static void	skip_whitespace(t_char_scanner *scanner)
{
	char_scanner_advance_while(scanner, WHITESPACE);
}

static void	tokenize_op(t_char_scanner *scanner,
	t_token_list **token_list, t_error *error)
{
	if (char_scanner_match(scanner, "&&"))
		token_list_add_op(token_list, T_AND_AND, error);
	else if (char_scanner_match(scanner, "||"))
		token_list_add_op(token_list, T_PIPE_PIPE, error);
	else if (char_scanner_match(scanner, "|"))
		token_list_add_op(token_list, T_PIPE, error);
	else if (char_scanner_match(scanner, "<<"))
		token_list_add_op(token_list, T_LESS_LESS, error);
	else if (char_scanner_match(scanner, "<"))
		token_list_add_op(token_list, T_LESS, error);
	else if (char_scanner_match(scanner, ">>"))
		token_list_add_op(token_list, T_GREAT_GREAT, error);
	else if (char_scanner_match(scanner, ">"))
		token_list_add_op(token_list, T_GREAT, error);
	else if (char_scanner_match(scanner, "("))
		token_list_add_op(token_list, T_PAREN_OPEN, error);
	else if (char_scanner_match(scanner, ")"))
		token_list_add_op(token_list, T_PAREN_CLOSE, error);
	else
		// Improve error message
		error_set_custom(error, strdup("Syntax error"));
}

static void	handle_single_quote(t_char_scanner *scanner, t_error *error)
{
	char_scanner_advance(scanner);
	char_scanner_advance_until(scanner, "'");
	if (!char_scanner_match(scanner, "'"))
		error_set_custom(error, strdup("Syntax error: Unclosed single quote."));
}

static void	handle_double_quote(t_char_scanner *scanner, t_error *error)
{
	char_scanner_advance(scanner);
	char_scanner_advance_until(scanner, "\"");
	if (!char_scanner_match(scanner, "\""))
		error_set_custom(error, strdup("Syntax error: Unclosed double quote."));
}

static void	tokenize_word(t_char_scanner *scanner, t_token_list **token_list,
	t_error *error)
{
	char	next_char;
	char	*extracted;

	next_char = char_scanner_peek(scanner);
	while (!char_scanner_is_at_end(scanner) && !is_metacharacter(next_char))
	{
		if (next_char == '\'')
			handle_single_quote(scanner, error);
		else if (next_char == '"')
			handle_double_quote(scanner, error);
		else
			char_scanner_advance(scanner);
		if (has_error(error))
			return ;
		next_char = char_scanner_peek(scanner);
	}
	extracted = char_scanner_extract(scanner, error);
	if (has_error(error))
		return ;
	token_list_add_word(token_list, extracted, error);
	if (has_error(error))
		free(extracted);
}

static void	tokenize_next(t_char_scanner *scanner, t_token_list **token_list,
	t_error *error)
{
	char	next_char;

	next_char = char_scanner_peek(scanner);

	if (is_whitespace(next_char))
		skip_whitespace(scanner);
	else if (is_metacharacter(next_char))
		tokenize_op(scanner, token_list, error);
	else
		tokenize_word(scanner, token_list, error);
}

t_token_list	*tokenize(char *src, t_error *error)
{
	t_char_scanner	scanner;
	t_token_list	*token_list;

	char_scanner_init(&scanner, src);
	token_list = NULL;
	while (!char_scanner_is_at_end(&scanner))
	{
		tokenize_next(&scanner, &token_list, error);
		if (has_error(error))
		{
			token_list_clear(token_list);
			return (NULL);
		}
		char_scanner_sync_start(&scanner);
	}
	token_list_add_op(&token_list, T_EOF, error);
	if (has_error(error))
		token_list_clear(token_list);
	return (token_list);
}
