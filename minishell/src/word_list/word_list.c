#include "word_list.h"

#include <stdlib.h>
#include "libft.h"
#include "ft_error.h"

static t_word_list	*create_node(char *word, t_error *error)
{
	t_word_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node)
	{
		new_node->next = NULL;
		new_node->word = word;
	}
	else
		error_set_system(error);
	return (new_node);
}

static void	destroy_node(t_word_list *node)
{
	free(node->word);
	free(node);
}

static t_word_list	*last_node(t_word_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	word_list_add(t_word_list **list, char *word, t_error *error)
{
	t_word_list	*new_node;

	new_node = create_node(word, error);
	if (has_error(error))
		return ;
	if (!*list)
		*list = new_node;
	else
		last_node(*list)->next = new_node;
}

void	word_list_clear(t_word_list *list)
{
	t_word_list	*next;

	while (list)
	{
		next = list->next;
		destroy_node(list);
		list = next;
	}
}

char	*word_list_to_string(t_word_list *list, t_error *error)
{
	char		*concatenated;
	int			len;
	t_word_list	*current;

	len = 0;
	current = list;
	while (current)
	{
		len += ft_strlen(current->word);
		current = current->next;
	}
	concatenated = malloc(sizeof(*concatenated) * (len + 1));
	if (!concatenated)
	{
		error_set_system(error);
		return (NULL);
	}
	while (list)
	{
		ft_strlcat(concatenated, list->word, len + 1);
		list = list->next;
	}
	concatenated[len] = '\0';
	return (concatenated);
}
