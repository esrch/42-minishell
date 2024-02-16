#include "expand.h"
#include "expand_internal.h"

#include <stdlib.h>
#include <string.h>

#include "env.h"
#include "libft.h"
#include "scanner.h"

/** Handle single quotes in the word.
 * 
 * Assumes that scanner is currently on the opening single quote.
 * Traverses until the closing single quote.
 * Parameters are ignored.
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	handle_single_quote(t_scanner *scanner, t_word_list **segments)
{
	(void)scanner_match(scanner, "'");
	scanner_advance_until(scanner, "'");
	(void)scanner_match(scanner, "'");
	if (scanner_is_at_end(scanner))
		return (extract_segment(scanner, segments));
	return (0);
}

/** Handle double quotes in the word.
 * 
 * Assumes that scanner is currently on the opening double quote.
 * Traverses until the closing double quote, and parses parameters if any.
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	handle_double_quote(t_scanner *scanner, t_word_list **segments)
{
	int	status;

	status = 0;
	(void) scanner_match(scanner, "\"");
	while (!scanner_match(scanner, "\""))
	{
		scanner_advance_until(scanner, "$\"");
		if (scanner_check(scanner, '$'))
			status = handle_param(scanner, segments);
		if (status != 0)
			return (status);
	}
	if (scanner_is_at_end(scanner))
		return (extract_segment(scanner, segments));
	return (status);
}

/** Handles "normal" characters in the word.
 * 
 * Returns 0 on success, and -1 on error.
*/
static int	handle_normal(t_scanner *scanner, t_word_list **segments)
{
	scanner_advance_until(scanner, "$'\"");
	if (scanner_is_at_end(scanner))
		return (extract_segment(scanner, segments));
	return (0);
}

/** Cleans up the temporary word list, and returns NULL
 * 
 * Returns NULL.
*/
static char	*cleanup(t_word_list *list)
{
	word_list_destroy(list);
	return (NULL);
}

/** Expands the parameters in a word.
 * 
 * Returns the expanded string on success, or NULL on error.
*/
char	*expand_params(char *word)
{
	t_word_list	*segments;
	t_scanner	scanner;
	char		*expanded;
	int			status;

	status = 0;
	segments = NULL;
	scanner_init(&scanner, word);
	while (!scanner_is_at_end(&scanner))
	{
		if (scanner_check(&scanner, '\''))
			status = handle_single_quote(&scanner, &segments);
		else if (scanner_check(&scanner, '"'))
			status = handle_double_quote(&scanner, &segments);
		else if (scanner_check(&scanner, '$'))
			status = handle_param(&scanner, &segments);
		else
			status = handle_normal(&scanner, &segments);
		if (status != 0)
			return (cleanup(segments));
	}
	expanded = word_list_to_str(segments);
	word_list_destroy(segments);
	return (expanded);
}