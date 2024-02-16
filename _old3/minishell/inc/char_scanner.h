#ifndef CHAR_SCANNER_H
# define CHAR_SCANNER_H

# include <stdbool.h>

typedef struct s_char_scanner
{
	char	*src;
	int		start;
	int		current;
}	t_char_scanner;

void	char_scanner_init(t_char_scanner *scanner, char *src);
char	char_scanner_peek(t_char_scanner *scanner);
char	char_scanner_advance(t_char_scanner *scanner);
void	char_scanner_advance_until(t_char_scanner *scanner, char *delim);
void	char_scanner_advance_while(t_char_scanner *scanner, char *skip);
bool	char_scanner_match(t_char_scanner *scanner, char *expected);
bool	char_scanner_is_at_end(t_char_scanner *scanner);
void	char_scanner_sync_start(t_char_scanner *scanner);
char	*char_scanner_extract(t_char_scanner *scanner);

#endif /* CHAR_SCANNER_H */