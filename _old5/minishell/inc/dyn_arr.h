#ifndef DYN_ARR_H
# define DYN_ARR_H

# include <stdlib.h>

typedef struct s_dyn_arr t_dyn_arr;

t_dyn_arr	*dyn_arr_create(void);
t_dyn_arr	*dyn_arr_from_arr(void **src);
void		dyn_arr_destroy(t_dyn_arr *arr,
				void (*destroy_val_f)(void *value));
void		**dyn_arr_to_arr(t_dyn_arr *arr);
size_t		dyn_arr_len(t_dyn_arr *arr);
void		*dyn_arr_get(t_dyn_arr *arr, size_t index);
int			dyn_arr_set(t_dyn_arr *arr, size_t index, void *value);
int			dyn_arr_push(t_dyn_arr *arr, void *value);
void		*dyn_arr_pop(t_dyn_arr *arr);
int			dyn_arr_insert(t_dyn_arr *arr, size_t index, void *value);
int			dyn_arr_insert_sorted(t_dyn_arr *arr, void *value,
				int (*cmp)(void *, void *));
void		*dyn_arr_remove(t_dyn_arr *arr, size_t index);
void		dyn_arr_foreach(t_dyn_arr *arr, void (*f)(void *value, void *arg),
				void *arg);

#endif