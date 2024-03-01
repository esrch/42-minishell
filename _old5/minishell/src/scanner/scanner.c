#include "scanner.h"

#include <stdbool.h>

/** Initializes the scanner.
 * 
*/
void	scanner_init(t_scanner *scanner, char *src)
{
	scanner->src = src;
	scanner->start = 0;
	scanner->current = 0;
}

/** Returns the current character.
 * 
*/
char	scanner_peek(t_scanner *scanner)
{
	return scanner->src[scanner->current];
}

/** Checks whether current character is equal to expected.
 * 
*/
bool	scanner_check(t_scanner *scanner, char expected)
{
	return (scanner_peek(scanner) == expected);
}

/** Checks whether the current position is at the end.
 * 
 * True if current character is '\0'.
*/
bool	scanner_is_at_end(t_scanner *scanner)
{
	return (scanner_check(scanner, '\0'));
}
