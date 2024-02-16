#ifndef FT_ERROR_H
# define FT_ERROR_H

# include <stdbool.h>

typedef enum e_error_type
{
	ERR_NONE,
	ERR_SYSTEM,
	ERR_CUSTOM
}	t_error_type;

typedef struct s_error
{
	t_error_type	type;
	char			*msg;
}	t_error;

void	error_init(t_error *error);
void	error_cleanup(t_error *error);
void	error_set_system(t_error *error);
void	error_set_custom(t_error *error, char *msg);
void	error_print(t_error *error);
void	error_print_custom(char *msg);
void	error_print_system(void);
bool	has_error(t_error *error);

#endif