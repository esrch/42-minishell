#include "libtest_utils.h"

static int	_test_errors = 0;

void	test_suite_init(t_test_suite *test_suite, char *name)
{
	test_suite->name = name;
	test_suite->error_count = 0;
	test_suite->tests = NULL;
}

void	test_suite_cleanup(t_test_suite *test_suite)
{
	t_test	*current;
	t_test	*next;

	current = test_suite->tests;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	test_suite_add_test(t_test_suite *test_suite, char *name, t_test_fn fn)
{
	t_test	*new_test;
	t_test	*last_test;

	new_test = malloc(sizeof(*new_test));
	if (!new_test)
	{
		printf("Error allocating memory to add a test.\n");
		exit(1);
	}
	new_test->name = name;
	new_test->fn = fn;
	new_test->next = NULL;
	if (test_suite->tests == NULL)
	{
		test_suite->tests = new_test;
		return ;
	}
	last_test = test_suite->tests;
	while (last_test->next)
		last_test = last_test->next;
	last_test->next = new_test;
}

void	test_suite_run(t_test_suite *test_suite)
{
	t_test	*current_test;

	printf(UNDERLINE(BOLD("\nTEST SUITE: %s\n")), test_suite->name);
	current_test = test_suite->tests;
	while (current_test)
	{
		printf(UNDERLINE("\nTest: %s\n"), current_test->name);
		_test_errors = 0;
		current_test->fn();
		test_suite->error_count += _test_errors;
		_test_errors = 0;
		current_test = current_test->next;
	}
	if (test_suite->error_count == 0)
	{
		printf(UNDERLINE(BOLD("\nTEST SUITE: %s :")), test_suite->name);
		printf(BOLD(GREEN(" Success\n\n")));
	}
	else
	{
		printf(UNDERLINE(BOLD("\nTEST SUITE: %s :")), test_suite->name);
		printf(BOLD(RED(" %d errors\n\n")), test_suite->error_count);
	}
	test_suite_cleanup(test_suite);
}

void	inc_test_errors(void)
{
	_test_errors++;
}