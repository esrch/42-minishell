#ifndef WORD_LIST_H
# define WORD_LIST_H

# include "ft_error.h"

typedef struct s_word_list
{
	struct s_word_list	*next;
	char				*word;
}	t_word_list;

void	word_list_add(t_word_list **list, char *word, t_error *error);
void	word_list_clear(t_word_list *list);
char	*word_list_to_string(t_word_list *list, t_error *error);
char	**word_list_to_array(t_word_list *list, t_error *error);

#endif /* WORD_LIST_H */