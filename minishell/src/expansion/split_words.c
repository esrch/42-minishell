#include "expansion_internal.h"

#include <string.h>
#include <stdlib.h>
#include "../../inc/char_scanner.h"
#include "../../inc/word_list.h"
#include "../../inc/error.h"

static void	handle_delimiter(t_char_scanner *scanner, char *delimiters)
{
	char_scanner_advance_while(scanner, delimiters);
	char_scanner_sync_start(scanner);
}

static void	handle_non_delimiter(t_char_scanner *scanner,
	t_word_list **word_list, char *delimiters, t_error *error)
{
	char			*word;

	char_scanner_advance_until(scanner, delimiters);
	word = char_scanner_extract(scanner, error);
	if (has_error(error))
		free(word);
	else
		word_list_add(word_list, word, error);
}

t_word_list	*split_words(char *s, char *delimiters, t_error *error)
{
	t_char_scanner	scanner;
	t_word_list		*word_list;

	char_scanner_init(&scanner, s);
	word_list = NULL;
	while (!char_scanner_is_at_end(&scanner))
	{
		// Remove depency on <string.h>
		if (strchr(delimiters, char_scanner_peek(&scanner)))
			handle_delimiter(&scanner, delimiters);
		else
			handle_non_delimiter(&scanner, &word_list, delimiters, error);
		if (has_error(error))
		{
			word_list_clear(&word_list);
			return (NULL);
		}
	}
	return (word_list);
}
