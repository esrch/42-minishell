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