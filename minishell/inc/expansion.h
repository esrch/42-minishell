#ifndef EXPANSION_H
# define EXPANSION_H

# include "ft_error.h"
# include "hash_map.h"
# include "word_list.h"

t_word_list	*expand_word(char *word, char *dir_path, t_hash_map *env,
				t_error *error);
t_word_list	*expand_list(t_word_list *words, char *dir_path, t_hash_map *env,
				t_error *error);
t_word_list	*expand_params(char *s, t_hash_map *env);
t_word_list	*expand_wildcard(char *dir_path, char *pattern);
t_word_list	*expand_split_words(char *s);
void		expand_unquote(char *s);

#endif