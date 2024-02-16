#ifndef ENV_LIST_H
# define ENV_LIST_H

# include "ft_error.h"

void	env_init(char **envp, t_error *error);
void	env_destroy(void);
char	*env_get(char *key);
void	env_set(char *key, char *value, t_error *error);
void	env_unset(char *key);
char	**env_to_arr(t_error *error);

#endif