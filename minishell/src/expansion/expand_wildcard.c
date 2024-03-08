#include "expansion.h"
#include "expansion_internal.h"

#include "directory.h"
#include "ft_error.h"
#include "libft.h"
#include "wildcard.h"
#include "word_list.h"

/** Returns a list with only the given word,
 * or NULL on error.
 * 
*/
static t_word_list	*handle_no_match(char *word)
{
	t_word_list	*list;

	list = NULL;
	if (word_list_add(&list, word) != 0)
		return (NULL);
	return (list);
}

/** If the word contains a star outside of quotes,
 * expands it to a list of matching files within the current directory.
 * 
 * If there is no match, returns a word list with a copy of the original
 * word.
 * 
 * Returns the list of matches, or NULL on error.
*/
t_word_list	*expand_wildcard(char *dir_path, char *word)
{
	t_word_list	*files;
	t_word_list	*current;
	t_word_list	*next;

	if (!ft_strchr(word, '*'))
		return (handle_no_match(word));
	files = directory_content(dir_path);
	if (!files)
		return (NULL);
	current = files;
	while (current)
	{
		next = current->next;
		if (current->word[0] == '.' && word[0] != '.')
			word_list_remove(&files, current);
		else if (current->word[0] == '.'
			&& !wildcard_match(word, current->word))
			word_list_remove(&files, current);
		else if (!wildcard_match(word, current->word))
			word_list_remove(&files, current);
		current = next;
	}
	if (!files)
		return (handle_no_match(word));
	return (files);
}
