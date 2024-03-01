#ifndef SCANNER_INTERNAL_H
# define SCANNER_INTERNAL_H

typedef struct s_scanner
{
	char	*src;
	int		start;
	int		current;
}	t_scanner;

#endif