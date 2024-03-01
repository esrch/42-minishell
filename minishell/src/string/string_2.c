#include "string.h"
#include "string_internal.h"

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

/** Compares the string to a C-style string.
 * 
 * Gives the same result as strcmp:
 * Returns 1 if the string is greater than the C-style string,
 * -1 if the string is smaller, 0 if equal.
*/
int	string_cmp(t_string *s, char *chars)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (i == s->len && !chars[i])
			return (0);
		if (!chars[i])
			return (1);
		if (i == s->len)
			return (-1);
		if (s->arr[i] > chars[i])
			return (1);
		if (s->arr[i] < chars[i])
			return (-1);
		i++;
	}
}

/** Compares the string to a C-style string.
 * 
 * Gives the same result as strcmp:
 * Returns 1 if the string is greater than the C-style string,
 * -1 if the string is smaller, 0 if equal.
*/
int	string_ncmp(t_string *s, char *chars, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (i == s->len && !chars[i])
			return (0);
		if (!chars[i])
			return (1);
		if (i == s->len)
			return (-1);
		if (s->arr[i] > chars[i])
			return (1);
		if (s->arr[i] < chars[i])
			return (-1);
		i++;
	}
	return (0);
}

/** Appends a C-style string to the given string.
 * 
 * If chars is NULL, has no effect.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	string_append(t_string *s, char *chars)
{
	size_t	chars_len;
	size_t	i;

	if (!chars)
		return (0);
	chars_len = ft_strlen(chars);
	if (s->len + chars_len > s->capacity
		&& string_resize(s, s->len + chars_len) != 0)
		return (-1);
	i = chars_len;
	while (i--)
		s->arr[s->len + i] = chars[i];
	s->len += chars_len;
	return (0);
}

/** Appends a character to the string.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	string_append_char(t_string *s, char c)
{
	if (s->len + 1 > s->capacity
		&& string_resize(s, s->len + 1) != 0)
		return (-1);
	s->arr[s->len] = c;
	s->len++;
	return (0);
}