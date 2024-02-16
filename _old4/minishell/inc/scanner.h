#ifndef SCANNER_H
# define SCANNER_H

# include <stdbool.h>

# include "ft_error.h"

typedef struct s_scanner
{
	char	*src;
	int		start;
	int		current;
}	t_scanner;

void	scanner_init(t_scanner *scanner, char *src);
char	scanner_peek(t_scanner *scanner);
bool	scanner_check(t_scanner *scanner, char expected);
char	scanner_advance(t_scanner *scanner);
void	scanner_advance_until(t_scanner *scanner, char *delim);
void	scanner_advance_while(t_scanner *scanner, char *chars);
bool	scanner_match(t_scanner *scanner, char *expected);
bool	scanner_is_at_end(t_scanner *scanner);
void	scanner_skip(t_scanner *scanner);
char	*scanner_extract(t_scanner *scanner, t_error *error);

#endif