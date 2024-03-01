#ifndef FT_ERROR_OLD_H
# define FT_ERROR_OLD_H

# include <stdbool.h>

typedef enum e_error_type
{
	E_NONE,
	E_SYSTEM,
	E_CUSTOM
}	t_error_type;

typedef struct s_error
{
	t_error_type	type;
	char			*msg;
}	t_error;

void	error_init(t_error *error);
bool	has_error(t_error *error);
void	error_set_system(t_error *error);
void	error_set_custom(t_error *error, char *msg);
void	error_clear(t_error *error);
void	error_print_system(char *prefix);
void	error_print_custom(char *msg);
void	error_print(t_error *error);

#endif