#include "libtest_utils.h"
#include "ft_sprintf.h"

static void	test_basic_ops(void)
{
	char	*s;

	s = ft_sprintf("Some text, %s, %%, %c, %b", "more text", 'a');
	assert_str_eq("Sets the right string", "Some text, more text, %, a, %b", s);
	free(s);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "FT_Sprintf");
	test_suite_add_test(&test_suite, "Basic operation", test_basic_ops);
	test_suite_run(&test_suite);
}