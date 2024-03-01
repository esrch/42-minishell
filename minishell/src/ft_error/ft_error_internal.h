#ifndef FT_ERROR_INTERNAL_H
# define FT_ERROR_INTERNAL_H

#include "ft_error.h"

typedef enum e_error_type
{
	ERR_NONE,
	ERR_SYSTEM,
	ERR_CUSTOM
}	t_error_type;

struct s_error
{
	t_error_type	type;
	int				code;
	char			*msg;
};

#endif