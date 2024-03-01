#include "word_list.h"

#include <stdlib.h>

#include "libft.h"

/** Creates a new word list node from a word.
 * 
 * Copies the word before adding it to the node.
*/
static t_word_list	*word_list_create_node(char *word)
{
	t_word_list	*new_node;
	char		*word_cpy;
	
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	word_cpy = ft_strdup(word);
	if (!word_cpy)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	new_node->word = word_cpy;
	return (new_node);
}

/** Adds a copy of word to the given list.
 * 
 * The word is first copied before being added.
 * 
 * Returns 0 on success, or -1 on allocation error.
*/
int	word_list_add(t_word_list **list, char *word)
{
	t_word_list	*new_node;

	if (!list)
		return (-1);
	new_node = word_list_create_node(word);
	if (!new_node)
		return (-1);
	if (!*list)
		*list = new_node;
	else
		word_list_last(*list)->next = new_node;
	return (0);
}

/** Adds a copy of word to the given list,
 * inserting it in alphabetical order.
 * 
 * The word is first copied before being added.
 * Assumes that the list is already sorted.
 * 
 * Returns 0 on success, or -1 on allocation error.
*/
int		word_list_add_sorted(t_word_list **list, char *word)
{
	t_word_list	*new_node;
	t_word_list	*current_node;

	if (!list)
		return (0);
	new_node = word_list_create_node(word);
	current_node = *list;
	if (!current_node || ft_strcmp(current_node->word, word) >= 0)
	{
		new_node->next = current_node;
		*list = new_node;
		return (0);
	}
	while (current_node->next
		&& ft_strcmp(current_node->next->word, word) < 0)
		current_node = current_node->next;
	new_node->next = current_node->next;
	current_node->next = new_node;
	return (0);
}

/** Frees the memory allocated for a word list
 * 
*/
void	word_list_destroy(t_word_list *list)
{
	t_word_list	*next_node;

	while (list)
	{
		next_node = list->next;
		free(list->word);
		free(list);
		list = next_node;
	}
}
