#include "wildcard.h"

#include <stdbool.h>

/** Handles single and double quotes in the pattern.
 * 
 * Returns true pattern and str match, otherwise false.
*/
static bool	match_quotes(char *pattern, char *str, char quote)
{
	while (1)
	{
		if (!*pattern)
			return (true);
		if (*pattern == quote)
			return (wildcard_match(pattern + 1, str));
		if (*pattern != *str)
			return (false);
		if (!*str)
			return (false);
		str++;
		pattern++;
	}
}

/** Handles a star in the pattern.
 * 
 * Returns true if pattern and str match, otherwise false.
*/
static bool match_star(char *pattern, char *str)
{
	while (1)
	{
		if (wildcard_match(pattern, str))
			return (true);
		if (!*str)
			return (false);
		str++;
	}
}

/** Checks whether a string matches a pattern.
 * 
 * Handles * as a wildcard. Ignores single and double quotes in the string.
*/
bool	wildcard_match(char *pattern, char *str)
{
	while (1)
	{
		if (!*pattern)
			return (true);
		if (*pattern == '"')
			return (match_quotes(pattern + 1, str, '"'));
		if (*pattern == '\'')
			return (match_quotes(pattern + 1, str, '\''));
		if (*pattern == '*')
			return (match_star(pattern + 1, str));
		if (*pattern != *str)
			return (false);
		if (!*str)
			return (false);
		str++;
		pattern++;
	}
}