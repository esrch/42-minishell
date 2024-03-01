#include "tokenize.h"
#include "tokenize_internal.h"

#include "ft_error.h"
#include "ft_sprintf.h"
#include "libft.h"
#include "scanner.h"
#include "token_list.h"

/** Destroys the scanner, the token list, and the token,
 * and returns NULL
 * 
*/
static t_token_list	*handle_error(t_scanner *scanner, t_token_list *tokens,
	t_token *token)
{
	if (scanner)
		scanner_destroy(scanner);
	if (scanner)
		token_list_destroy(tokens);
	if (token)
		token_destroy(token);
	return (NULL);
}

/** Converts a command (string) into a token list
 * 
 * Sets an error in case of error.
 * 
 * Returns the token list, or NULL in case of an error.
*/
t_token_list	*tokenize(char *cmd, t_error *error)
{
	t_scanner		*scanner;
	t_token_list	*tokens;
	t_token			*token;

	scanner = scanner_create(cmd);
	if (!scanner)
		return (handle_error(scanner, NULL, NULL));
	tokens = NULL;
	while (!scanner_is_at_end(scanner))
	{
		token = next_token(scanner, error);
		if (ft_has_error(error))
			return (handle_error(scanner, tokens, NULL));
		if (token && token_list_add(&tokens, token) != 0)
			return (handle_error(scanner, tokens, token));
		scanner_skip(scanner);
	}
	scanner_destroy(scanner);
	if (token_list_add_op(&tokens, T_EOF) != 0)
		return (handle_error(NULL, tokens, NULL));
	return (tokens);
}

/** Returns the next token in the scanner.
 * 
 * Returns the next token (can be NULL in case of a space),
 * or NULL on error.
*/
t_token	*next_token(t_scanner *scanner, t_error *error)
{
	char	next_char;

	next_char = scanner_peek(scanner);
	if (ft_strchr(TOKENIZE_WHITESPACE, next_char))
	{
		scanner_advance_while(scanner, TOKENIZE_WHITESPACE);
		return (NULL);
	}
	if (ft_strchr(TOKENIZE_METACHARACTERS, next_char))
		return (next_op_token(scanner, error));
	return (next_word_token(scanner, error));
}
