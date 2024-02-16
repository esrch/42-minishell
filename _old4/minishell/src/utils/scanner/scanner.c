#include "scanner.h"

#include <stdbool.h>
#include <stdlib.h>

#include "ft_error.h"
#include "libft.h"

void	scanner_init(t_scanner *scanner, char *src)
{
	scanner->src = src;
	scanner->start = 0;
	scanner->current = 0;
}

char	scanner_peek(t_scanner *scanner)
{
	return (scanner->src[scanner->current]);
}

bool	scanner_check(t_scanner *scanner, char expected)
{
	return (scanner_peek(scanner) == expected);
}

char	scanner_advance(t_scanner *scanner)
{
	char	c;

	c = scanner_peek(scanner);
	scanner->current++;
	return (c);
}

void	scanner_advance_until(t_scanner *scanner, char *delim)
{
	while (!scanner_is_at_end(scanner)
			&& !ft_strchr(delim, scanner_peek(scanner)))
		scanner->current++;
}

void	scanner_advance_while(t_scanner *scanner, char *chars)
{
	while (!scanner_is_at_end(scanner)
			&& ft_strchr(chars, scanner_peek(scanner)))
		scanner->current++;
}

bool	scanner_match(t_scanner *scanner, char *expected)
{
	int	i;

	i = 0;
	while (expected[i])
	{
		if (expected[i] != scanner->src[scanner->current + i])
			return (false);
		i++;
	}
	scanner->current += i;
	return (true);
}

bool	scanner_is_at_end(t_scanner *scanner)
{
	return (scanner_peek(scanner) == '\0');
}

void	scanner_skip(t_scanner *scanner)
{
	scanner->start = scanner->current;
}

char	*scanner_extract(t_scanner *scanner, t_error *error)
{
	char	*extracted;
	int		len;

	len = scanner->current - scanner->start;
	extracted = malloc(sizeof(*extracted) * (len + 1));
	if (!extracted)
	{
		error_set_system(error);
		return (NULL);
	}
	ft_strlcpy(extracted, scanner->src + scanner->start, len + 1);
	scanner_skip(scanner);
	return (extracted);
}