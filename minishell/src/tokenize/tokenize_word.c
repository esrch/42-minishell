#include "tokenize.h"
#include "tokenize_internal.h"

#include "ft_error.h"
#include "scanner.h";

/** Handle single quoted strings within a word
 * 
*/
static void	handle_single_quote(t_scanner *scanner, t_error *error)
{
	scanner_advance(scanner);
	scanner_advance_until(scanner, "'");
	if (!scanner_match(scanner, "'"))
		error_set_custom(error, ft_strdup("syntax error: Missing closing single quote."));
}

/** Handle double quoted strings within a word
 * 
*/
static void	handle_double_quote(t_scanner *scanner, t_error *error)
{
	scanner_advance(scanner);
	scanner_advance_until(scanner, "\"");
	if (!scanner_match(scanner, "\""))
		error_set_custom(error, ft_strdup("syntax error: Missing closing double quote."));
}

/** Extracts a string from a scanner and add it to the token list
 * 
*/
static void	add_extracted_word(t_scanner *scanner, t_token_list **token_list,
	t_error *error)
{
	char	*extracted;

	extracted = scanner_extract(scanner);
	if (!extracted)
	{
		error_set_system(error);
		return ;
	}
	if (token_list_add_word(token_list, extracted) != 0)
	{
		free(extracted);
		error_set_system(error);
	}
}

/** Adds a word token to the token list
 * 
*/
void	tokenize_word(t_scanner *scanner, t_token_list **token_list, t_error *error)
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
	add_extracted_word(scanner, token_list, error);
}
