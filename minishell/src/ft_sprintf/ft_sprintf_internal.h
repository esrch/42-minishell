#ifndef FT_SPRINTF_INTERNAL_H
# define FT_SPRINTF_INTERNAL_H

int		ft_sprintf_len(char *format, va_list args);
void	ft_sprintf_fill(char *format, va_list args, char *result);

#endif