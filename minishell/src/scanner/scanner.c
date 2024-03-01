#include "scanner.h"
#include "scanner_internal.h"

#include <stdbool.h>
#include <stdlib.h>

#include "libft.h"

/** Creates a new character scanner.
 * 
 * src is the string to scan, and should not be NULL.
 * 
 * Returns the scanner, or NULL on error.
*/
t_scanner	*scanner_create(char *src)
{
	t_scanner	*scanner;

	scanner = malloc(sizeof(*scanner));
	if (!scanner)
		return (NULL);
	scanner->start = 0;
	scanner->current = 0;
	scanner->src = ft_strdup(src);
	if (!scanner->src)
	{
		free(scanner);
		return (NULL);
	}
	return (scanner);
}

/** Frees the memory for the scanner.
 * 
*/
void	scanner_destroy(t_scanner *scanner)
{
	if (!scanner)
		return ;
	free(scanner->src);
	free(scanner);
}

/** Returns the current character.
 * 
*/
char	scanner_peek(t_scanner *scanner)
{
	return scanner->src[scanner->current];
}

/** Returns the character after the current one.
 * 
 * If the scanner is already at the end, returns the NULL character.
*/
char	scanner_peek_next(t_scanner *scanner)
{
	if (scanner_is_at_end(scanner))
		return '\0';
	return (scanner->src[scanner->current + 1]);
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
