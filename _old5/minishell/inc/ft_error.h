#ifndef FT_ERROR_H
# define FT_ERROR_H

# include <stdbool.h>

typedef struct s_error	t_error;

t_error	*ft_error_create(void);
void	ft_error_destroy(t_error *error);
void	ft_error_reset(t_error *error);
char	*ft_error_prefix(char *prefix);
bool	ft_has_error(t_error *error);
void	ft_error_set_system(t_error *error);
void	ft_error_set_custom(t_error *error, int code, char *msg);
int		ft_error_get_code(t_error *error);
void	ft_error_print(t_error *error);
void	ft_error_print_system(void);
void	ft_error_print_custom(char *msg);

#endif