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
void	assert_eq_int(char *msg, int expected, int value);
void	assert_eq_str(char *msg, char *expected, char *value);
void	assert_eq_true(char *msg, bool expected);

#endif /* TEST_UTILS_H */