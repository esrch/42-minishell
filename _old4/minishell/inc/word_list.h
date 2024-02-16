#ifndef WORD_LIST_H
# define WORD_LIST_H

# include "ft_error.h"

typedef struct s_word_list
{
	struct s_word_list	*next;
	char				*word;
}	t_word_list;

void	word_list_add(t_word_list **list, char *word, t_error *error);
void	word_list_add_sorted(t_word_list **list, char *word, t_error *error);
void	word_list_destroy(t_word_list *list);
void	word_list_append(t_word_list **list, t_word_list *addition);
void	word_list_replace(t_word_list **list, t_word_list *to_be_replaced,
			t_word_list *replacement);
char	**word_list_to_arr(t_word_list *list, t_error *error);
char	*word_list_to_str(t_word_list *list, t_error *error);

#endif