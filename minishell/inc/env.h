#ifndef ENV_H
# define ENV_H

int		env_init(char **envp);
void	env_destroy(void);
int		env_set(char *key, char *value);
void	env_unset(char *key);
char	*env_get(char *key);
char	**env_to_arr(void);

#endif