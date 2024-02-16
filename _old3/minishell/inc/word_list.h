#ifndef WORD_LIST_H
# define WORD_LIST_H

# include "defines.h"

typedef struct s_word_list
{
	struct s_word_list	*next;
	char				*word;
}	t_word_list;

t_status	word_list_add(t_word_list **list, char *word);
void		word_list_clear(t_word_list *list);
char		*word_list_to_string(t_word_list *list);
char		**word_list_to_array(t_word_list *list);

#endif /* WORD_LIST_H */