#include "dyn_arr.h"
#include "dyn_arr_internal.h"

#include <stdlib.h>

/** Removes the last element of the array, and returns it.
 * 
 * Returns the last element of the array, or NULL if it is empty.
*/
void	*dyn_arr_pop(t_dyn_arr *arr)
{
	void	*value;

	if (arr->len == 0)
		return (NULL);
	value = arr->elements[arr->len - 1];
	arr->len--;
	return (value);
}

/** Inserts an element at the given index.
 * 
 * Shifts all elements after the given index forward.
 * If the index is larger than the array length or 0,
 * does nothing and returns -1.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	dyn_arr_insert(t_dyn_arr *arr, size_t index, void *value)
{
	size_t	i;

	if (index > arr->len)
		return (-1);
	if (index == arr->len)
		return (dyn_arr_push(arr, value));
	if (arr->len == arr->capacity && dyn_arr_resize(arr) != 0)
		return (-1);
	i = arr->len;
	while (i > index)
	{
		arr->elements[i] = arr->elements[i - 1];
		i--;
	}
	arr->elements[index] = value;
	arr->len++;
	return (0);
}

/** Inserts an element in a sorted array.
 * 
 * Assumes that the given array is already sorted.
 * cmp is a comparison function similar to strcmp, that returns 1 if the first
 * argument is bigger, -1 if it is smaller, and 0 if both arguments are equal.
*/
int	dyn_arr_insert_sorted(t_dyn_arr *arr, void *value,
	int (*cmp)(void *, void *))
{
	size_t	low;
	size_t	mid;
	size_t	high;

	if (arr->len == 0)
		return (dyn_arr_push(arr, value));
	low = 0;
	high = arr->len - 1;
	while (low < high)
	{
		mid = low + (high - low) / 2;
		if (cmp(value, arr->elements[mid]) > 0)
			low = mid + 1;
		else if (cmp(value, arr->elements[mid]) < 0)
			high = mid - 1;
		else
			return (dyn_arr_insert(arr, mid, value));
	}
	if (cmp(value, arr->elements[low]) > 0)
		return (dyn_arr_insert(arr, low + 1, value));
	return (dyn_arr_insert(arr, low, value));
}

/** Removes and returns the element at the given index.
 * 
 * Returns the removed element, or NULL if the index is out of range.
*/
void	*dyn_arr_remove(t_dyn_arr *arr, size_t index)
{
	void	*value;
	size_t	i;

	if (index >= arr->len)
		return (NULL);
	value = arr->elements[index];
	i = index;
	while (i < arr->len - 1)
	{
		arr->elements[i] = arr->elements[i + 1];
		i++;
	}
	arr->len--;
	return (value);
}

/** Applies the foreach_f to each element of the array.
 * 
 * The foreach_f function is called with the current value as the first
 * argument, and arg as the second argument.
*/
void	dyn_arr_foreach(t_dyn_arr *arr, void (*f)(void *value, void *arg),
	void *arg)
{
	size_t	i;

	i = 0;
	while (i < arr->len)
	{
		f(arr->elements[i], arg);
		i++;
	}
}
