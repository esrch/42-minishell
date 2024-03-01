#include "dyn_arr.h"
#include "dyn_arr_internal.h"
#include "libft.h"

#include <stdlib.h>

/** Returns the array length.
 * 
*/
size_t	dyn_arr_len(t_dyn_arr *arr)
{
	return (arr->len);
}

/** Get an array element by index.
 * 
 * Returns the element at the given index,
 * or NULL if the index is out of range.
*/
void	*dyn_arr_get(t_dyn_arr *arr, size_t index)
{
	if (index >= arr->len)
		return (NULL);
	return (arr->elements[index]);
}

/** Sets an array element by value.
 * 
 * Returns 0 on success, or -1 if the index is out of range.
*/
int	dyn_arr_set(t_dyn_arr *arr, size_t index, void *value)
{
	if (index >= arr->len)
		return (-1);
	arr->elements[index] = value;
	return (0);
}

/** Adds an element at the end of the list.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	dyn_arr_push(t_dyn_arr *arr, void *value)
{
	if (arr->len == arr->capacity && dyn_arr_resize(arr) != 0)
			return (-1);
	arr->elements[arr->len] = value;
	arr->len++;
	return (0);
}
