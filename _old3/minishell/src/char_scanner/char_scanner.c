#include "char_scanner.h"

#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_error.h"

void	char_scanner_init(t_char_scanner *scanner, char *src)
{
	scanner->src = src;
	scanner->start = 0;
	scanner->current = 0;
}

char	char_scanner_peek(t_char_scanner *scanner)
{
	return (scanner->src[scanner->current]);
}

char	char_scanner_advance(t_char_scanner *scanner)
{
	char	c;

	c = char_scanner_peek(scanner);
	scanner->current++;
	return (c);
}

void	char_scanner_advance_until(t_char_scanner *scanner, char *delim)
{
	while (!char_scanner_is_at_end(scanner)
			&& !ft_strchr(delim, char_scanner_peek(scanner)))
		scanner->current++;
}

void	char_scanner_advance_while(t_char_scanner *scanner, char *skip)
{
	while (!char_scanner_is_at_end(scanner)
			&& ft_strchr(skip, char_scanner_peek(scanner)))
		scanner->current++;
}

bool	char_scanner_match(t_char_scanner *scanner, char *expected)
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

bool	char_scanner_is_at_end(t_char_scanner *scanner)
{
	return (char_scanner_peek(scanner) == '\0');
}

void	char_scanner_sync_start(t_char_scanner *scanner)
{
	scanner->start = scanner->current;
}

char	*char_scanner_extract(t_char_scanner *scanner)
{
	char	*extracted;
	int		len;

	len = scanner->current - scanner->start;
	extracted = malloc(sizeof(*extracted) * (len + 1));
	if (!extracted)
	{
		error_print_system();
		return (NULL);
	}
	ft_strlcpy(extracted, scanner->src + scanner->start, len + 1);
	char_scanner_sync_start(scanner);
	return (extracted);
}