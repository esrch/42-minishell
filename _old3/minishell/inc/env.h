#ifndef ENV_H
# define ENV_H

# include "defines.h"
# include "ft_error.h"

typedef struct s_kv_list
{
	struct s_kv_list	*next;
	char				*key;
	char				*value;
}	t_kv_list;

typedef t_kv_list	*t_env;

t_env		env_create(char **envp);
void		env_destroy(t_env env);
t_status	env_set(t_env *env, char *key, char *value);
void		env_unset(t_env *env, char *key);
char		*env_get(t_env env, char *key);

#endif /* ENV_H */