#include "dyn_arr.h"
#include "dyn_arr_internal.h"

#include <stdlib.h>

#include "libft.h"

/** Creates a new dynamic array.
 * 
 * destroy_value is a pointer to a function to free an array value.
 * It can be NULL, in which case the value is not freed when
 * the array is destroyed.
 * 
 * Returns the new array, or NULL on error.
*/
t_dyn_arr	*dyn_arr_create(void)
{
	t_dyn_arr	*arr;

	arr = malloc(sizeof(*arr));
	if (!arr)
		return (NULL);
	arr->len = 0;
	arr->capacity = DYN_ARR_CAPACITY;
	arr->elements = ft_calloc(arr->capacity, sizeof(void *));
	if (!arr->elements)
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}

/** Creates a dynamic array from an existing NULL-terminated array.
 * 
 * Returns the new array, or NULL on error.
*/
t_dyn_arr	*dyn_arr_from_arr(void **src)
{
	t_dyn_arr	*arr;
	size_t		len;

	len = 0;
	while (src[len])
		len++;
	arr = malloc(sizeof(*arr));
	if (!arr)
		return (NULL);
	arr->len = len;
	arr->capacity = len + DYN_ARR_CAPACITY;
	arr->elements = ft_calloc(arr->capacity, sizeof(void *));
	if (!arr->elements)
	{
		free(arr);
		return (NULL);
	}
	while (len--)
		arr->elements[len] = src[len];
	return (arr);
}

/** Destroys a dynamic array.
 * 
 * elem_destroy is a pointer to a function that frees the memory
 * of an array element.
*/
void	dyn_arr_destroy(t_dyn_arr *arr, void (*destroy_val_f)(void *value))
{
	size_t	i;

	if (destroy_val_f)
	{
		i = 0;
		while (i < arr->len)
		{
			destroy_val_f(arr->elements[i]);
			i++;
		}
	}
	free(arr->elements);
	free(arr);
}

/** Doubles the array capacity.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	dyn_arr_resize(t_dyn_arr *arr)
{
	void	**new_elements;
	size_t	i;

	new_elements = ft_calloc(arr->capacity * DYN_ARR_RESIZE_FACTOR,
		sizeof(void *));
	if (!new_elements)
		return (-1);
	i = 0;
	while (i < arr->len)
	{
		new_elements[i] = arr->elements[i];
		i++;
	}
	free(arr->elements);
	arr->elements = new_elements;
	arr->capacity *= DYN_ARR_RESIZE_FACTOR;
	return (0);
}

/** Returns a normal void** array from a dynamic array.
 * 
 * Returns a NULL-terminated array on success, or NULL on error.
*/
void	**dyn_arr_to_arr(t_dyn_arr *arr)
{
	void	**result;
	size_t	i;

	result = ft_calloc(arr->len + 1, sizeof(void *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < arr->len)
	{
		result[i] = arr->elements[i];
		i++;
	}
	return (result);
}
