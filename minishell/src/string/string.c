#include "string.h"
#include "string_internal.h"

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

/** Creates a new string
 * 
 * The initial capacity is twice the length chars,
 * or 12, whichever is greatest.
 * 
 * Returns the new string, or NULL on error.
*/
t_string	*string_create(char *chars)
{
	t_string	*s;
	size_t		i;

	if (!chars)
		return (NULL);
	s = malloc(sizeof(*s));
	if (!s)
		return (NULL);
	s->len = ft_strlen(chars);
	if (s->len >= 6)
		s->capacity = s->len * 2;
	else
		s->capacity = 12;
	s->arr = ft_calloc(s->capacity, sizeof(char));
	if (!s->arr)
	{
		free(s);
		return (NULL);
	}
	i = s->len;
	while (i--)
		s->arr[i] = chars[i];
	return (s);
}

/** Frees the memory associated with the given string.
 * 
*/
void		string_destroy(t_string *s)
{
	if (!s)
		return ;
	free(s->arr);
	free(s);
}

/** Resizes the given string.
 * 
 * Doubles the capacity of the string, until it reaches at least min_capacity.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	string_resize(t_string *s, size_t min_capacity)
{
	size_t	new_capacity;
	char	*new_arr;
	size_t	i;
	
	if (s->capacity >= min_capacity)
		return (0);
	new_capacity = s->capacity;
	while (new_capacity < min_capacity)
		new_capacity *= 2;
	new_arr = ft_calloc(new_capacity, sizeof(char));
	if (!new_arr)
		return (-1);
	i = s->len;
	while (i--)
		new_arr[i] = s->arr[i];
	free(s->arr);
	s->arr = new_arr;
	return (0);
}

/** Returns the length of the string
 * 
*/
size_t		string_len(t_string *s)
{
	return (s->len);
}

/** Returns the character at a given index.
 * 
 * Does not perform bounds checks. Accessing a character at
 * an index out of bounds has undefined behavior.
 * 
 * Returns the character.
*/
char		string_at(t_string *s, size_t index)
{
	return (s->arr[index]);
}
