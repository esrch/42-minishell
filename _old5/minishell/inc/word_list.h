#ifndef WORD_LIST_H
# define WORD_LIST_H

typedef struct s_word_list
{
	struct s_word_list	*next;
	char				*word;
}	t_word_list;

int		word_list_add(t_word_list **list, char *word);
int		word_list_add_sorted(t_word_list **list, char *word);
void	word_list_destroy(t_word_list *list);
void	word_list_append(t_word_list **list, t_word_list *addition);
int		word_list_len(t_word_list *list);
char	*word_list_to_str(t_word_list *list);
char	**word_list_to_arr(t_word_list *list);
void	word_list_print(t_word_list *list);

#endif