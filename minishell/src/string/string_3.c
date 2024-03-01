#include "string.h"
#include "string_internal.h"

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

/** Inserts a string at the given index.
 * 
 * If index is greater than the string length, does nothing.
 * If chars is NULL, has no effect.
 * If index is equal to string length, adds chars at the end of the string.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	string_insert(t_string *s, size_t index, char *chars)
{
	size_t	chars_len;
	size_t	i;

	if (!chars || index > s->len)
		return (0);
	chars_len = ft_strlen(chars);
	if (s->len + chars_len > s->capacity
		&& string_resize(s, s->len + chars_len) != 0)
		return (-1);
	i = 0;
	while (i < s->len - index)
	{
		s->arr[s->len + chars_len - i - 1] = s->arr[s->len - i - 1];
		i++;
	}
	i = 0;
	while (i < chars_len)
	{
		s->arr[index + i] = chars[i];
		i++;
	}
	s->len += chars_len;
	return (0);
}

/** Erases count characters in a string starting at index.
 * 
 * Erases as many characters as available (doesn't overflow).
*/
void	string_erase(t_string *s, size_t index, size_t count)
{
	size_t	i;

	if (index >= s->len || count == 0)
		return ;
	if (index + count > s->len)
		count = s->len - index;
	i = 0;
	while (index + count + i < s->len)
	{
		s->arr[index + i] = s->arr[index + count + i];
		i++;
	}
	s->len -= count;
}

/** Replaces characters in a string.
 * 
 * Combines erase and insert in one function.
 * If count is 0, doesn't erase anything.
 * If chars is NULL, doesn't insert anything.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	string_replace(t_string *s, size_t index, size_t count, char *chars)
{
	string_erase(s, index, count);
	return (string_insert(s, index, chars));
}

/** Returns a normal char array from the given string
 * 
 * Returns the char array, or NULL on error.
*/
char	*string_to_chars(t_string *s)
{
	char	*chars;
	
	chars = malloc(sizeof(*chars) * (s->len + 1));
	if (!chars)
		return (NULL);
	ft_strlcpy(chars, s->arr, s->len + 1);
	return (chars);
}