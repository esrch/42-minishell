#include "tokenizer.h"

#include <stdlib.h>

#include "ft_error.h"
#include "ft_sprintf_malloc.h"
#include "libft.h"
#include "scanner.h"
#include "token_list.h"

static bool	is_whitespace(char c)
{
	return ft_strchr(WHITESPACE, c) != NULL;
}

static bool	is_metacharacter(char c)
{
	return ft_strchr(METACHARACTERS, c) != NULL;
}

static void	skip_whitespace(t_scanner *scanner)
{
	scanner_advance_while(scanner, WHITESPACE);
}

static void	tokenize_op(t_scanner *scanner, t_token_list **token_list,
	t_error *error)
{
	if (scanner_match(scanner, "&&"))
		return (token_list_add_op(token_list, T_AND, error));
	else if (scanner_match(scanner, "||"))
		return (token_list_add_op(token_list, T_OR, error));
	else if (scanner_match(scanner, "|"))
		return (token_list_add_op(token_list, T_PIPE, error));
	else if (scanner_match(scanner, "<<"))
		return (token_list_add_op(token_list, T_REDIR_HEREDOC, error));
	else if (scanner_match(scanner, "<"))
		return (token_list_add_op(token_list, T_REDIR_IN, error));
	else if (scanner_match(scanner, ">>"))
		return (token_list_add_op(token_list, T_REDIR_APPEND, error));
	else if (scanner_match(scanner, ">"))
		return (token_list_add_op(token_list, T_REDIR_OUT, error));
	else if (scanner_match(scanner, "("))
		return (token_list_add_op(token_list, T_PAREN_OPEN, error));
	else if (scanner_match(scanner, ")"))
		return (token_list_add_op(token_list, T_PAREN_CLOSE, error));
	else
		error_set_custom(error, ft_sprintf_malloc(
			"syntax error near unexpected '%c'", scanner_peek(scanner)));
	return ;
}

static void	handle_single_quote(t_scanner *scanner, t_error *error)
{
	scanner_advance(scanner);
	scanner_advance_until(scanner, "'");
	if (!scanner_match(scanner, "'"))
		error_set_custom(error, ft_strdup("syntax error: Missing closing single quote."));
}

static void	handle_double_quote(t_scanner *scanner, t_error *error)
{
	scanner_advance(scanner);
	scanner_advance_until(scanner, "\"");
	if (!scanner_match(scanner, "\""))
		error_set_custom(error, ft_strdup("syntax error: Missing closing double quote."));
}

static void	tokenize_word(t_scanner *scanner, t_token_list **token_list, t_error *error)
{
	char		next_char;
	char		*extracted;

	next_char = scanner_peek(scanner);
	while (!scanner_is_at_end(scanner) && !is_metacharacter(next_char))
	{
		if (next_char == '\'')
			handle_single_quote(scanner, error);
		else if (next_char == '"')
			handle_double_quote(scanner, error);
		else
			scanner_advance(scanner);
		if (has_error(error))
			return ;
		next_char = scanner_peek(scanner);
	}
	extracted = scanner_extract(scanner, error);
	if (!has_error(error))
		token_list_add(token_list, T_WORD, extracted, error);
	if (has_error(error))
		free(extracted);
}

static void	tokenize_next(t_scanner *scanner, t_token_list **token_list, t_error *error)
{
	char		next_char;

	next_char = scanner_peek(scanner);
	if (is_whitespace(next_char))
		skip_whitespace(scanner);
	else if (is_metacharacter(next_char))
		tokenize_op(scanner, token_list, error);
	else
		tokenize_word(scanner, token_list, error);
}

t_token_list	*tokenize(char *src, t_error *error)
{
	t_scanner		scanner;
	t_token_list	*token_list;

	scanner_init(&scanner, src);
	token_list = NULL;
	while (!scanner_is_at_end(&scanner))
	{
		tokenize_next(&scanner, &token_list, error);
		if (has_error(error))
		{
			token_list_destroy(token_list);
			return (NULL);
		}
		scanner_skip(&scanner);
	}
	token_list_add_op(&token_list, T_EOF, error);
	if (has_error(error))
	{
		token_list_destroy(token_list);
		return (NULL);
	}
	return (token_list);
}