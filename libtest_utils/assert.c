#include "libtest_utils.h"

void	assert_section(char *title)
{
	if (title)
		printf(DIM("\n%s\n"), title);
	else
		printf("\n");
}
void	assert_msg(char *msg)
{
	printf(GREEN("%s\n"), msg);
}

void	assert_int_eq(char *msg, int expected, int value)
{
	ASSERT_EXPECTED(expected == value, d, msg, expected, value);
}

void	assert_char_eq(char *msg, char expected, char value)
{
	ASSERT_EXPECTED(expected == value, c, msg, expected, value);
}

void	assert_str_eq(char *msg, char *expected, char *value)
{
	ASSERT_EXPECTED(strcmp(expected, value) == 0, s, msg, expected, value);
}

void	assert_addr_eq(char *msg, void *expected, void *value)
{
	ASSERT_EXPECTED(expected == value, p, msg, expected, value);
}

void	assert_true(char *msg, bool value)
{
	ASSERT_EXPECTED(value, s, msg, "true", "false");
}

void	assert_false(char *msg, bool value)
{
	ASSERT_EXPECTED(!value, s, msg, "false", "true");
}

void	assert_null(char *msg, void *value)
{
	ASSERT_EXPECTED(value == NULL, s, msg, "NULL", "Not NULL");
}

void	assert_not_null(char *msg, void *value)
{
	ASSERT_EXPECTED(value != NULL, s, msg, "Not NULL", "NULL");
}