#ifndef GLOBAL_H
# define GLOBAL_H

# include <stdbool.h>

char	*prog_name(char *argv0);
int		last_exit_status(int status);
int		in_subprocess(int new_value);

#endif