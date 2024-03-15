#include "libtest_utils.h"
#include "prog_name.h"

static void	test_no_slash(void)
{
	prog_name("abc");
	assert_str_eq("Program name correct", "abc", prog_name(NULL));
}

static void	test_with_slash(void)
{
	assert_section("Program name: /abc");
	prog_name("/abc");
	assert_str_eq("Program name correct", "abc", prog_name(NULL));

	assert_section("Program name: ./abc");
	prog_name("./abc");
	assert_str_eq("Program name correct", "abc", prog_name(NULL));
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Program name");
	test_suite_add_test(&test_suite, "Name with no slash", test_no_slash);
	test_suite_add_test(&test_suite, "Name with slash", test_with_slash);
	test_suite_run(&test_suite);
}