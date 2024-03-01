#ifndef STRING_H
# define STRING_H

# include <stdlib.h>

typedef struct s_string	t_string;

t_string	*string_create(char *chars);
void		string_destroy(t_string *s);
size_t		string_len(t_string *s);
char		string_at(t_string *s, size_t index);
int			string_cmp(t_string *s, char *chars);
int			string_ncmp(t_string *s, char *chars, size_t n);
int			string_append(t_string *s, char *chars);
int			string_append_char(t_string *s, char c);
int			string_insert(t_string *s, size_t index, char *chars);
void		string_erase(t_string *s, size_t index, size_t count);
int			string_replace(t_string *s, size_t index, size_t len,
				char *chars);
char		*string_to_chars(t_string *s);

#endif