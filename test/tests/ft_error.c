#include "libtest_utils.h"
#include "ft_error.h"
#include "libft.h"

#include <unistd.h>

static void	test_basic_ops(void)
{
	t_error	*error;
	
	assert_section("System error");
	error = ft_error_create();
	assert_true("Initialized with no error", !ft_has_error(error));
	assert_int_eq("Error code set to 0", 0, ft_error_get_code(error));
	ft_error_set_system(error);
	assert_true("System error set", ft_has_error(error));
	assert_int_eq("Error code set to 0", 0, ft_error_get_code(error));

	assert_section("Reset error");
	ft_error_reset(error);
	assert_true("No error", !ft_has_error(error));
	assert_int_eq("Error code set at 0", 0, ft_error_get_code(error));

	assert_section("Custom error");
	ft_error_set_custom(error, 2, ft_strdup("Custom error"));
	assert_true("Error set", ft_has_error(error));
	assert_int_eq("Error code set", 2, ft_error_get_code(error));
	assert_str_eq("Error message set", "Custom error", ft_error_get_msg(error));
	ft_error_destroy(error);

	assert_msg("Manual check: No leak");
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "FT_Error");
	test_suite_add_test(&test_suite, "Basic operations", test_basic_ops);
	test_suite_run(&test_suite);
}