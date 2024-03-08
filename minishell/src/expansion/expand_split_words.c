#include "expansion.h"

#include "libft.h"
#include "scanner.h"

/** Frees the allocated resources if needed, and sets the system error.
 * 
 * Returns NULL.
*/
static t_word_list	*handle_error(t_scanner *scanner, t_word_list *words)
{
	if (scanner)
		scanner_destroy(scanner);
	if (words)
		word_list_destroy(words);
	return (NULL);
}

static int	extract_word(t_scanner *scanner, t_word_list **words)
{
	int		result;
	char	*extracted;

	extracted = scanner_extract(scanner);
	if (!extracted)
		return (-1);
	if (!*extracted)
	{
		free(extracted);
		return (0);
	}
	scanner_advance_while(scanner, " \t");
	scanner_skip(scanner);
	result = word_list_add(words, extracted);
	free(extracted);
	return (result);
}

/** Traverses the string in the scanner to extract words.
 * 
 * Returns 0 on success, or -1 on error.
*/
static int	traverse_string(t_scanner *scanner, t_word_list **words)
{
	scanner_advance_while(scanner, " \t");
	scanner_skip(scanner);
	while (!scanner_is_at_end(scanner))
	{
		if (scanner_check(scanner, ' ') || scanner_check(scanner, '\t'))
		{
			if (extract_word(scanner, words) != 0)
				return (-1);
		}
		else if (scanner_match(scanner, "\""))
		{
			scanner_advance_until(scanner, "\"");
			scanner_match(scanner, "\"");
		}
		else if (scanner_match(scanner, "'"))
		{
			scanner_advance_until(scanner, "'");
			scanner_match(scanner, "'");
		}
		else
			scanner_advance(scanner);
	}
	if (extract_word(scanner, words) != 0)
		return (-1);
	return (0);
}

/** Handles the case when the initial string is empty or NULL.
 * 
 * Returns a list with one element, which is a string of length 0.
 * Returns NULL in case of error.
*/
static t_word_list	*handle_empty_string(void)
{
	t_word_list	*words;

	words = NULL;
	if (word_list_add(&words, "") != 0)
		return (NULL);
	return (words);
}

/** Splits the string s into words, taking single and double
 * quotes into account.
 * 
 * Returns the list of words, NULL if the list is empty,
 * or NULL on error.
*/
t_word_list	*expand_split_words(char *s)
{
	t_word_list	*words;
	t_scanner	*scanner;

	if (!s || !*s)
		return (handle_empty_string());
	words = NULL;
	scanner = scanner_create(s);
	if (!scanner)
		return (handle_error(scanner, words));
	if (traverse_string(scanner, &words) != 0)
		return (handle_error(scanner, words));
	scanner_destroy(scanner);
	return (words);
}
