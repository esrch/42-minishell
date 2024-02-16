#include "expand.h"
#include "expand_internal.h"

#include <stdbool.h>
#include <stdlib.h>

#include "scanner.h"
#include "word_list.h"

/** Checks if a character is whitespace.
 * 
 * Whitespace is space, tab or newline.
*/
static bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/** Skips whitespace.
 * 
*/
static void	handle_whitespace(t_scanner *scanner)
{
	scanner_advance_while(&scanner, " \t\n");
	scanner_skip(&scanner);
}

/** Handles a word.
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	handle_char(t_scanner *scanner, t_word_list **split_str)
{
	char	*extracted;
	int		status;

	extracted = NULL;
	while (!scanner_is_at_end(scanner) && !is_whitespace(scanner_peek(scanner)))
	{
		if (scanner_match(scanner, "\""))
		{
			scanner_advance_until(scanner, "\"");
			(void) scanner_match(scanner, "\"");
		}
		else if (scanner_match(scanner, "'"))
		{
			scanner_advance_until(scanner, "'");
			(void) scanner_match(scanner, "'");
		}
		else
			(void) scanner_advance(scanner);
	}
	extracted = scanner_extract(scanner);
	if (!extracted)
		return (-1);
	status = word_list_add(split_str, extracted);
	free(extracted);
	return (status);
}

/** Split words within a string into a word list.
 * 
 * Accounts for spaces within single and double quotes.
 * 
 * Returns the word list, or NULL on error.
*/
t_word_list	*split_words(char *str)
{
	t_word_list	*split_str;
	int			status;
	t_scanner	scanner;

	status = 0;
	split_str = NULL;
	scanner_init(&scanner, str);
	while (!scanner_is_at_end(&scanner))
	{
		if (is_whitespace(scanner_peek(&scanner)))
			handle_whitespace(&scanner);
		else
			status = handle_char(&scanner, &split_str);
		if (status != 0)
		{
			word_list_destroy(split_str);
			return (NULL);
		}
	}
	return (split_str);
}
