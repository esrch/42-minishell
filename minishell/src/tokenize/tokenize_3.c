#include "tokenize.h"
#include "tokenize_internal.h"

#include "ft_error.h"
#include "libft.h"
#include "scanner.h"

/** Handle single quoted strings within a word
 * 
*/
static void	handle_single_quote(t_scanner *scanner, t_error *error)
{
	char	*error_msg;

	scanner_advance(scanner);
	scanner_advance_until(scanner, "'");
	if (!scanner_match(scanner, "\""))
	{
		error_msg = ft_strdup("syntax error: missing closing single quote.");
		if (!error_msg)
			ft_error_set_system(error);
		else
			ft_error_set_custom(error, 0, error_msg);
	}
}

/** Handle double quoted strings within a word
 * 
*/
static void	handle_double_quote(t_scanner *scanner, t_error *error)
{
	char	*error_msg;

	scanner_advance(scanner);
	scanner_advance_until(scanner, "\"");
	if (!scanner_match(scanner, "\""))
	{
		error_msg = ft_strdup("syntax error: missing closing double quote.");
		if (!error_msg)
			ft_error_set_system(error);
		else
			ft_error_set_custom(error, 0, error_msg);
	}
}

/** Extract the word from the scanner, and return a word token
 * created from it.
 * 
 * Returns the token, or NULL on error.
*/
static t_token	*extracted_token(t_scanner *scanner, t_error *error)
{
	char	*extracted;
	t_token	*token;

	extracted = scanner_extract(scanner);
	if (!extracted)
	{
		ft_error_set_system(error);
		return (NULL);
	}
	token = token_create_word(extracted);
	if (!token)
	{
		free(extracted);
		ft_error_set_system(error);
	}
	return (token);
}

/** Returns the next word token.
 * 
 * Returns the token, or NULL on error.
*/
t_token	*next_word_token(t_scanner *scanner, t_error *error)
{
	char	next_char;

	next_char = scanner_peek(scanner);
	while (!scanner_is_at_end(scanner)
		&& !ft_strchr(TOKENIZE_METACHARACTERS, next_char))
	{
		if (next_char == '\'')
			handle_single_quote(scanner, error);
		else if (next_char == '"')
			handle_double_quote(scanner, error);
		else
			scanner_advance(scanner);
		if (ft_has_error(error))
			return (NULL);
		next_char = scanner_peek(scanner);
	}
	return (extracted_token(scanner, error));
}