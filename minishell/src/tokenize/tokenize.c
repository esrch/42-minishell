#include "tokenize.h"
#include "tokenize_internal.h"

#include <stdlib.h>

#include "ft_error.h"
#include "ft_sprintf.h"
#include "libft.h"
#include "scanner.h"
#include "token_list.h"

static void	tokenize_next(t_scanner *scanner, t_token_list **token_list,
	t_error *error);

/** Converts a command (string) into a token list
 * 
 * Sets an error in case of error.
 * 
 * Returns the token list, or NULL in case of an error.
*/
t_token_list	*tokenize(char *cmd, t_error *error)
{
	t_scanner		scanner;
	t_token_list	*token_list;

	scanner_init(&scanner, cmd);
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
	if (token_list_add_op(&token_list, T_EOF) != 0)
	{
		error_set_system(error);
		token_list_destroy(token_list);
		return (NULL);
	}
	return (token_list);
}

/** Checks if the character is a whitespace.
 * 
 * Whitespace characters are space, tab and newline.
*/
static bool	is_whitespace(char c)
{
	return ft_strchr(WHITESPACE, c) != NULL;
}

/** Checks if the character is a metacharacter.
 * 
 * Metacharacters are space, tab, newline, <, >, |, &, ;, (, ).
*/
static bool	is_metacharacter(char c)
{
	return ft_strchr(METACHARACTERS, c) != NULL;
}

/** Add next token to given token list.
 * 
*/
static void	tokenize_next(t_scanner *scanner, t_token_list **token_list, t_error *error)
{
	char		next_char;

	next_char = scanner_peek(scanner);
	if (is_whitespace(next_char))
		scanner_advance_while(scanner, WHITESPACE);
	else if (is_metacharacter(next_char))
		tokenize_op(scanner, token_list, error);
	else
		tokenize_word(scanner, token_list, error);
}