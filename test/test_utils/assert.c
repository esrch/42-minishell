#include "test_utils.h"

static void	print_ok(char *msg)
{
	printf(GREEN("%s: OK\n"), msg);
}

void	assert_eq_str(char *msg, char *expected, char *value)
{
	if (strcmp(expected, value) == 0)
		print_ok(msg);
	else
	{
		printf(RED("\n%s: Error\nExpected : %s\nActual   : %s\n\n"),
			msg, expected, value);
		inc_test_errors();
	}
}

void	assert_eq_int(char *msg, int expected, int value)
{
	if (expected == value)
		print_ok(msg);
	else
	{
		printf(RED("\n%s: Error\nExpected : %d\nActual   : %d\n"),
			msg, expected, value);
		inc_test_errors();
	}
}

void	assert_eq_true(char *msg, bool expected)
{
	if (expected)
		print_ok(msg);
	else
	{
		printf(RED("\n%s: Error\nExpected : true\nActual   : false\n"),
			msg);
		inc_test_errors();
	}
}