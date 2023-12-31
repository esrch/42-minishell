#include "test_utils.h"

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

	printf(UNDERLINE(BOLD("\n%s\n")), test_suite->name);
	current_test = test_suite->tests;
	while (current_test)
	{
		printf("\nTest: %s\n", current_test->name);
		_test_errors = 0;
		current_test->fn();
		test_suite->error_count += _test_errors;
		_test_errors = 0;
		current_test = current_test->next;
	}
	if (test_suite->error_count == 0)
		printf(GREEN("\n%s: No errors\n\n"), test_suite->name);
	else
		printf(RED("\n%s: %d errors\n\n"), test_suite->name, test_suite->error_count);
	test_suite_cleanup(test_suite);
}

void	inc_test_errors(void)
{
	_test_errors++;
}