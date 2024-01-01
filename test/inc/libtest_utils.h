#ifndef TEST_UTILS_H
# define TEST_UTILS_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>

# define BOLD(text) "\x1b[1m"text"\x1b[22m"
# define UNDERLINE(text) "\x1b[4m"text"\x1b[24m"
# define RED(text) "\x1b[31m"text"\x1b[0m"
# define GREEN(text) "\x1b[32m"text"\x1b[0m"
# define DIM(text) "\x1b[2m"text"\x1b[22m"

# define ASSERT_EXPECTED(assertion, printf_fmt, msg, expected, value) \
	if (assertion) \
		printf(GREEN("%s: OK\n"), msg); \
	else \
	{ \
		printf(RED( \
			"\n%s: Error\n" \
			"Expected : %" #printf_fmt "\n" \
			"Actual   : %" #printf_fmt "\n\n"), \
			msg, expected, value); \
		inc_test_errors(); \
	}

typedef void	(*t_test_fn)(void);

typedef struct s_test
{
	char			*name;
	t_test_fn		fn;
	struct s_test	*next;
}	t_test;

typedef struct s_test_suite
{
	char	*name;
	int		error_count;
	t_test	*tests;
}	t_test_suite;

// Test suite.
void	test_suite_init(t_test_suite *test_suite, char *name);
void	test_suite_cleanup(t_test_suite *test_suite);
void	test_suite_add_test(t_test_suite *test_suite, char *name, t_test_fn fn);
void	test_suite_run(t_test_suite *test_suite);
void	inc_test_errors(void);

// Assert.
void	assert_section(char *title);
void	assert_msg(char *msg);
void	assert_int_eq(char *msg, int expected, int value);
void	assert_char_eq(char *msg, char expected, char value);
void	assert_str_eq(char *msg, char *expected, char *value);
void	assert_addr_eq(char *msg, void *expected, void *value);
void	assert_true(char *msg, bool value);
void	assert_false(char *msg, bool value);
void	assert_null(char *msg, void *value);
void	assert_not_null(char *msg, void *value);

#endif /* TEST_UTILS_H */