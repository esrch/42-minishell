#include "word_list.h"

#include <stdlib.h>

#include "libft.h"

/** Removes an element from the list.
 * 
*/
void	word_list_remove(t_word_list **list, t_word_list *element)
{
	t_word_list	*curr;
	t_word_list	*prev;

	if (!list || !*list || !element)
		return ;
	curr = *list;
	prev = NULL;
	while (curr)
	{
		if (curr == element)
			break ;
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	if (!prev)
		*list = curr->next;
	else
		prev->next = curr->next;
	curr->next = NULL;
	word_list_destroy(curr);
}

/** Removes empty (NULL or empty string) elements from the list.
 * 
*/
void	word_list_remove_empty(t_word_list **list)
{
	t_word_list	*curr;
	t_word_list	*prev;
	t_word_list	*next;

	curr = *list;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		if (!curr->word || ft_strlen(curr->word) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*list = curr->next;
			free(curr->word);
			free(curr);
		}
		else
			prev = curr;
		curr = next;
	}
}

/** Converts a word list to a string.
 * 
 * Returns the created string, or NULL on error.
*/
char	*word_list_to_str(t_word_list *list)
{
	char		*str;
	int			len;
	t_word_list	*list_cpy;

	len = 0;
	list_cpy = list;
	while (list_cpy)
	{
		len += ft_strlen(list_cpy->word);
		list_cpy = list_cpy->next;
	}
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	str[0] = '\0';
	while (list)
	{
		ft_strlcat(str, list->word, len + 1);
		list = list->next;
	}
	return (str);
}

/** Converts a word list to a string array.
 * 
 * Returns the created array, or NULL on error.
*/
char	**word_list_to_arr(t_word_list *list)
{
	char		**arr;
	int			len;
	int			i;

	len = word_list_len(list);
	arr = malloc(sizeof(*arr) * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (list)
	{
		arr[i] = ft_strdup(list->word);
		if (!arr[i])
		{
			ft_free_2d_count((void ***) arr, i);
			return (NULL);
		}
		i++;
		list = list->next;
	}
	arr[i] = NULL;
	return (arr);
}

/** Prints the word list as a space separated list
 * 
*/
void	word_list_print(t_word_list *list)
{
	if (!list)
		return ;
	while (list->next)
	{
		ft_printf("%s ", list->word);
		list = list->next;
	}
	ft_printf("%s", list->word);
}
