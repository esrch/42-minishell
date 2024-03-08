#include "libtest_utils.h"
#include "expansion.h"

#include "libft.h"

static void	test_basic_ops(void)
{
	char	*s;

	s = ft_strdup("ab\"c 'd\"ef'g\"h \"'i");
	expand_unquote(s);
	assert_str_eq("Unquoted correctly", "abc 'defg\"h \"i", s);
	free(s);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Expansion: Unquote");
	test_suite_add_test(&test_suite, "Basic operations", test_basic_ops);
	test_suite_run(&test_suite);
}