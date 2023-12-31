#include "../includes/minishell.h"

static bool	handle_wildcard(char *pattern, char *word);
		
static bool	handle_chars(char *pattern, char *word)
{
	while (1)
	{
		if (*pattern == '*')
			return (handle_wildcard(pattern, word));
		if (*pattern != *word)
			return (false);
		if (!*pattern)
			return (true);
		pattern++;
		word++;
	}
}

bool	handle_wildcard(char *pattern, char *word)
{
	while (*pattern == '*')
		pattern++;
	if (!*pattern)
		return (true);
	while (*word)
	{
		if (*word == *pattern && handle_chars(pattern, word))
			return (true);
		word++;
	}
	return (false);
}

bool	wildcard_match(char *pattern, char *word)
{
	if (*pattern == '*')
		return (handle_wildcard(pattern, word));
	return (handle_chars(pattern, word));
}