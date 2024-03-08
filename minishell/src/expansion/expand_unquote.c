#include "expansion.h"

#include <stdbool.h>

/** Unquotes the given string in place.
 * 
 * Top-level single and double quotes are removed from s.
*/
void	expand_unquote(char *s)
{
	int	i;
	int	j;
	bool	in_single_quotes;
	bool	in_double_quotes;

	i = 0;
	j = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	while (s[j])
	{
		if (!in_double_quotes && s[j] == '\'')
		{
			in_single_quotes = !in_single_quotes;
			j++;
		}
		else if (!in_single_quotes && s[j] == '"')
		{
			in_double_quotes = !in_double_quotes;
			j++;
		}
		else
			s[i++] = s[j++];
	}
	s[i] = '\0';
}