#include "word_list.h"

#include <stdlib.h>

#include "ft_error.h"
#include "libft.h"

static void	word_list_destroy_node(t_word_list *node)
{
	free(node->word);
	free(node);
}

static t_word_list	*word_list_last(t_word_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

static int	word_list_len(t_word_list *list)
{
	int	len;

	len = 0;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}

void	word_list_add(t_word_list **list, char *word, t_error *error)
{
	t_word_list	*new_node;

	if (!list)
		return ;
	new_node = malloc(sizeof(*new_node));
	if (new_node)
	{
		new_node->next = NULL;
		new_node->word = word;
	}
	else
		error_set_system(error);
	if (!*list)
		*list = new_node;
	else
		word_list_last(*list)->next = new_node;
}

void	word_list_add_sorted(t_word_list **list, char *word, t_error *error)
{
	t_word_list	*new_node;
	t_word_list	*current_node;

	if (!list)
		return ;
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
	{
		error_set_system(error);
		return ;
	}
	new_node->word = word;
	if (!*list || ft_strncmp((*list)->word, word, ft_strlen(word) + 1) >= 0)
	{
		new_node->next = *list;
		*list = new_node;
		return ;
	}
	current_node = *list;
	while (current_node->next && ft_strncmp(current_node->next->word, word,
			ft_strlen(word) + 1) < 0)
		current_node = current_node->next;
	new_node->next = current_node->next;
	current_node->next = new_node;
}

void	word_list_destroy(t_word_list *list)
{
	t_word_list	*next_node;

	while (list)
	{
		next_node = list->next;
		word_list_destroy_node(list);
		list = next_node;
	}
}

void	word_list_append(t_word_list **list, t_word_list *addition)
{
	if (!*list)
		*list = addition;
	else
		word_list_last(*list)->next = addition;
}

void	word_list_replace(t_word_list **list, t_word_list *to_be_replaced,
	t_word_list *replacement)
{
	t_word_list	**current;
	t_word_list	*next_node;

	if (!list || !*list || !to_be_replaced || !replacement)
		return ;
	current = list;
	while (*current != to_be_replaced)
		current = &(*current)->next;
	if (!*current)
		return ;
	next_node = (*current)->next;
	word_list_destroy_node(*current);
	*current = replacement;
	word_list_last(replacement)->next = next_node;
}

static char	**word_list_to_arr_cleanup(char **arr, int i, t_error *error)
{
	error_set_system(error);
	while (i--)
		free(arr[i]);
	free(arr);
	return (NULL);
}

char	**word_list_to_arr(t_word_list *list, t_error *error)
{
	int		i;
	int		len;
	char	**arr;
	char	*word_cpy;

	len = word_list_len(list);
	arr = malloc(sizeof(*arr) * (len + 1));
	if (!arr)
	{
		error_set_system(error);
		return (NULL);
	}
	i = 0;
	while (list)
	{
		word_cpy = ft_strdup(list->word);
		if (!word_cpy)
			return (word_list_to_arr_cleanup(arr, i, error));
		arr[i] = word_cpy;
		i++;
		list = list->next;
	}
	arr[len] = NULL;
	return (arr);
}

char	*word_list_to_str(t_word_list *list, t_error *error)
{
	char		*str;
	int			len;
	t_word_list	*list_cpy;

	len = 0;
	list_cpy = list;
	while (list_cpy)
	{
		if (list_cpy->word)
			len += ft_strlen(list_cpy->word);
		list_cpy = list_cpy->next;
	}
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
	{
		error_set_system(error);
		return (NULL);
	}
	str[0] = '\0';
	while (list)
	{
		if (list->word)
			ft_strlcat(str, list->word, len + 1);
		list = list->next;
	}
	return (str);
}