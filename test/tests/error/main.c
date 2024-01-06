#include "minishell_test.h"
#include <errno.h>
#include <stdio.h>

void	test_error_init(void)
{
	t_error	error;

	error_init(&error);
	assert_int_eq("Sets error type to no error", ERR_NONE, error.type);
	assert_null("Sets error message to NULL", error.msg);
}

void	test_error_set(void)
{
	t_error	error;
	char	*error_msg;

	error_msg = ft_strdup("Error message");
	error_init(&error);
	error_set(&error, ERR_SYSTEM, error_msg);
	assert_int_eq("Sets correct error type", ERR_SYSTEM, error.type);
	assert_str_eq("Sets correct error message", error_msg, error.msg);
	free(error_msg);
}

void	test_error_cleanup(void)
{
	t_error	error;
	char	*error_msg;

	error_msg = ft_strdup("Error message");
	error_set(&error, ERR_SYSTEM, error_msg);
	error_cleanup(&error);
	assert_int_eq("Resets error type to no error", ERR_NONE, error.type);
	assert_null("Resets error message to NULL", error.msg);
	assert_msg("Test with valgrind: No leak");
}

void	test_error_print(void)
{
	t_error	error;
	char	*error_msg;

	error_msg = ft_strdup("Error message");

	assert_section("Doesn't print a message if no error");
	error_set(&error, ERR_NONE, NULL);
	error_print(&error, "<prompt>");
	assert_msg("Manual test: Check that it doesn't print a message");

	assert_section("Prints system error, with prompt");
	error_set(&error, ERR_SYSTEM, NULL);
	errno = ENOENT;
	error_print(&error, "<prompt>");
	assert_msg("Manual test: Check that it prints ENOENT message with prompt");
	errno = 0;

	assert_section("Prints system error, with no prompt");
	error_set(&error, ERR_SYSTEM, NULL);
	errno = ENOENT;
	error_print(&error, NULL);
	assert_msg("Manual test: Check that it prints ENOENT message with no prompt");
	errno = 0;

	assert_section("Prints custom error, with prompt");
	error_set(&error, ERR_CUSTOM, error_msg);
	errno = ENOENT;
	error_print(&error, "<prompt>");
	assert_msg("Manual test: Check that it prints \"Error message\" with prompt");
	errno = 0;

	assert_section("Prints custom error, with no prompt");
	error_set(&error, ERR_CUSTOM, error_msg);
	errno = ENOENT;
	error_print(&error, NULL);
	assert_msg("Manual test: Check that it prints \"Error message\" with no prompt");
	errno = 0;

	error_cleanup(&error);
}

void	test_has_error(void)
{
	t_error	error;

	assert_section("ERR_NONE");
	error.type = ERR_NONE;
	assert_false("Gives no error", has_error(&error));

	assert_section("ERR_SYSTEM");
	error.type = ERR_SYSTEM;
	assert_true("Gives an error", has_error(&error));

	assert_section("ERR_CUSTOM");
	error.type = ERR_CUSTOM;
	assert_true("Gives an error", has_error(&error));

	assert_section("NULL error");
	assert_true("Gives an error", has_error(NULL));
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Error");

	test_suite_add_test(&test_suite, "Error init", test_error_init);
	test_suite_add_test(&test_suite, "Error set", test_error_set);
	test_suite_add_test(&test_suite, "Error cleanup", test_error_cleanup);
	test_suite_add_test(&test_suite, "Error print", test_error_print);
	test_suite_add_test(&test_suite, "Has error", test_has_error);

	test_suite_run(&test_suite);
}