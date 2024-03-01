#ifndef STRING_INTERNAL_H
# define STRING_INTERNAL_H

# include "string.h"

# include <stdlib.h>

typedef struct s_string
{
	size_t	capacity;
	size_t	len;
	char	*arr;
}	t_string;

int	string_resize(t_string *s, size_t min_capacity);

#endif