#include "minishell_test.h"

# define ASSERT_MATCH(pattern, str) \
	assert_true(pattern " == " str, pattern_match(pattern, str))
# define ASSERT_NO_MATCH(pattern, str) \
	assert_true(pattern " != " str, !pattern_match(pattern, str))

void	test_pattern_match(void)
{
	ASSERT_MATCH("Hello", "Hello");
	ASSERT_MATCH("Hel*", "Hello");
	ASSERT_MATCH("H*l*o", "He    llo");
	ASSERT_NO_MATCH("Hel*p", "Hell");
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Pattern match");

	test_suite_add_test(&test_suite, "Test match", test_pattern_match);

	test_suite_run(&test_suite);
}

#undef ASSERT_MATCH
#undef ASSERT_NO_MATCH