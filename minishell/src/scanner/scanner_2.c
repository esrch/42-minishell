#include "scanner.h"
#include "scanner_internal.h"

#include "libft.h"

/** Syncs start with current to skip all traversed characters.
 * 
*/
void	scanner_skip(t_scanner *scanner)
{
	scanner->start = scanner->current;
}

/** Extracts the traversed characters between start and current,
 * and moves start to current.
 * 
 * Returns the extracted string, or NULL in case of allocation error.
*/
char	*scanner_extract(t_scanner *scanner)
{
	char	*extracted;

	extracted = ft_substr(scanner->src, scanner->start,
		scanner->current - scanner->start);
	if (!extracted)
		return (NULL);
	scanner->start = scanner->current;
	return (extracted);
}

/** Checks whether the characters starting from current match expected
 * 
*/
bool	scanner_match(t_scanner *scanner, char *expected)
{
	int	len;

	len = ft_strlen(expected);
	if (ft_strncmp(expected, scanner->src + scanner->current, len) == 0)
	{
		scanner->current += len;
		return (true);
	}
	return (false);
}
