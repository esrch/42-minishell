#ifndef SCANNER_H
# define SCANNER_H

# include <stdbool.h>

typedef struct s_scanner	t_scanner;

t_scanner	*scanner_create(char *src);
void		scanner_destroy(t_scanner *scanner);
char		scanner_peek(t_scanner *scanner);
char		scanner_peek_next(t_scanner *scanner);
bool		scanner_check(t_scanner *scanner, char expected);
bool		scanner_is_at_end(t_scanner *scanner);
char		scanner_advance(t_scanner *scanner);
int			scanner_advance_until(t_scanner *scanner, char *delim);
int			scanner_advance_while(t_scanner *scanner, char *chars);
bool		scanner_match(t_scanner *scanner, char *expected);
void		scanner_skip(t_scanner *scanner);
char		*scanner_extract(t_scanner *scanner);

#endif