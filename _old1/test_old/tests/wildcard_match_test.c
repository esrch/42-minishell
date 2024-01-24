#include "minishell_test.h"

static char	*build_msg(char *pattern, char *comparison, char *str)
{
	char	*result;
	int		len;

	len = ft_strlen(pattern) + ft_strlen(comparison) + ft_strlen(str) + 1;
	result = malloc(sizeof(char) * len);
	ft_strlcpy(result, pattern, len);
	ft_strlcat(result, comparison, len);
	ft_strlcat(result, str, len);
	return (result);
}

void	test_match(char *pattern, char *str)
{
	char	*msg;

	msg = build_msg(pattern, " == ", str);
	assert_eq_true(msg, wildcard_match(pattern, str));
	free(msg);
}

void	test_no_match(char *pattern, char *str)
{
	char	*msg;

	msg = build_msg(pattern, " != ", str);
	assert_eq_true(msg, !wildcard_match(pattern, str));
	free(msg);
}

int	main(void)
{
	test_match("Hello", "Hello");
	test_match("Hel*", "Hello");
	test_match("Hel*o", "Hello");
	test_no_match("Hel*p", "Hel");
	test_no_match("Hel*p", "Hello");
	test_match("Hel*l*o", "Hello");
}