#include "expand.h"
#include "expand_internal.h"

#include "word_list.h"

/** Handles single quotes.
 * 
 * Skips any (non-single) quotes inside of single quotes.
*/
static void	handle_single_quote(char *word, int *index1_ptr, int *index2_ptr)
{
	int index1;
	int index2;

	index1 = *index1_ptr;
	index2 = *index2_ptr;
	index2++;
	while (word[index2] && word[index2] != '\'')
		word[index1++] = word[index2++];
	if (word[index2] == '\'')
		index2++;
	*index1_ptr = index1;
	*index2_ptr = index2;
}

/** Handles double quotes.
 * 
 * Skips any (non-double) quotes inside of double quotes.
*/
static void	handle_double_quote(char *word, int *index1_ptr, int *index2_ptr)
{
	int index1;
	int index2;

	index1 = *index1_ptr;
	index2 = *index2_ptr;
	index2++;
	while (word[index2] && word[index2] != '"')
		word[index1++] = word[index2++];
	if (word[index2] == '"')
		index2++;
	*index1_ptr = index1;
	*index2_ptr = index2;
}

/** Unquotes a word
 * 
*/
static void	unquote_word(char *word)
{
	int	index1;
	int	index2;

	index1 = 0;
	index2 = 0;
	while (word[index2])
	{
		if (word[index2] == '\'')
			handle_single_quote(word, &index1, &index2);
		else if (word[index2] == '"')
			handle_double_quote(word, &index1, &index2);
		else
			word[index1++] = word[index2++];
	}
	word[index1] = word[index2];
}

/** Unquote all words in the word list argv
 * 
*/
void	expand_unquote(t_word_list *argv)
{
	while (argv)
	{
		unquote_word(argv->word);
		argv = argv->next;
	}
}