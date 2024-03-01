#include "path.h"
#include "path_internal.h"

#include <stdbool.h>

#include "libft.h"
#include "scanner.h"

/** Returns the prefix for the current directory.
 * 
 * Also advances the scanner to after any ":".
 * 
 * Returns the prefix on success, or NULL on error.
*/
static char	*cwd_prefix(t_scanner *scanner)
{
	char	*prefix;

	prefix = ft_strdup("./");
	scanner_advance_while(scanner, ":");
	scanner_skip(scanner);
	return (prefix);
}

/** Extracts the next prefix from the path.
 * 
 * Assumes that the scanner is not yet at the end.
 * is_first should be true if we are at the beginning of the PATH
 * (because if it starts with a colon, it should include the
 * current directory in the path search).
 * Returns the prefix, or NULL on error.
*/
char	*next_prefix(t_scanner *scanner, bool is_first)
{
	char	next_char;

	next_char = scanner_advance(scanner);
	if (next_char == ':')
	{
		if (is_first)
			return (cwd_prefix(scanner));
		if (scanner_is_at_end(scanner))
			return (cwd_prefix(scanner));
		if (scanner_check(scanner, ':'))
			return (cwd_prefix(scanner));
		scanner_skip(scanner);
	}
	scanner_advance_until(scanner, ":");
	return (scanner_extract(scanner));
}