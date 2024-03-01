#include "libtest_utils.h"
#include "scanner.h"

static void	test_basic_ops(void)
{
	t_scanner	*scanner;
	char		c;

	assert_section("Create a scanner");
	scanner = scanner_create("ABC");
	assert_not_null("Creates a new scanner", scanner);

	assert_section("Peek");
	assert_char_eq("Can peek the next character", 'A', scanner_peek(scanner));

	assert_section("Advance");
	c = scanner_advance(scanner);
	assert_char_eq("Returns the next character", 'A', c);
	assert_char_eq("Moves to the next character", 'B', scanner_peek(scanner));
	assert_true("Not yet at the end", !scanner_is_at_end(scanner));
	
	assert_section("Is at end");
	scanner_advance(scanner);
	scanner_advance(scanner);
	assert_true("Is at end after moving forward twice more", scanner_is_at_end(scanner));

	scanner_destroy(scanner);
	assert_msg("Manual check: No leaks");
}

static void	test_peek_next(void)
{
	t_scanner	*scanner;

	scanner = scanner_create("ABC");
	assert_char_eq("Peek next returns the right character", 'B', scanner_peek_next(scanner));
	scanner_advance(scanner);
	scanner_advance(scanner);
	assert_char_eq("At the end, peek next returns '\0'", '\0', scanner_peek_next(scanner));
	scanner_destroy(scanner);
}

static void	test_check(void)
{
	t_scanner	*scanner;

	scanner = scanner_create("ABC");
	assert_true("Check is true when the character is correct", scanner_check(scanner, 'A'));
	assert_true("Check is false when the character is not correct", !scanner_check(scanner, 'B'));
	scanner_destroy(scanner);
}

static void	test_advance_until(void)
{
	t_scanner	*scanner;
	int			return_val;

	scanner = scanner_create("AAABAAAAAC");

	assert_section("First match");
	return_val = scanner_advance_until(scanner, "BC");
	assert_true("Advances to the first matching character", scanner_check(scanner, 'B'));
	assert_int_eq("Returns the number of characters traversed", 3, return_val);
	
	assert_section("Second match");
	scanner_advance(scanner);
	return_val = scanner_advance_until(scanner, "BC");
	assert_true("Advances to the second matching character", scanner_check(scanner, 'C'));
	assert_int_eq("Returns the number of characters traversed", 5, return_val);

	scanner_destroy(scanner);
}

static void	test_advance_while(void)
{
	t_scanner	*scanner;
	int			return_val;

	scanner = scanner_create("AAAABAAAAAAC");

	assert_section("First match");
	return_val = scanner_advance_while(scanner, "A");
	assert_true("Advances while the character matches", scanner_check(scanner, 'B'));
	assert_int_eq("Returns the number of characters traversed", 4, return_val);

	assert_section("Second match");
	return_val = scanner_advance_while(scanner, "AB");
	assert_true("Advances while the character matches", scanner_check(scanner, 'C'));
	assert_int_eq("Returns the number of characters traversed", 7, return_val);

	scanner_destroy(scanner);
}

static void	test_match(void)
{
	t_scanner	*scanner;

	scanner = scanner_create("ABC");
	assert_true("Match returns false when the character doesn't match", !scanner_match(scanner, "AC"));
	assert_true("Match doesn't move forward if the character doesn't match", scanner_check(scanner, 'A'));
	assert_true("Match returns true when the character matches", scanner_match(scanner, "AB"));
	assert_true("Match moves forward if the character matches", scanner_check(scanner, 'C'));
	scanner_destroy(scanner);
}

static void	test_skip_extract(void)
{
	t_scanner	*scanner;
	char		*extracted;

	scanner = scanner_create("abcdef");

	assert_section("Extract");
	scanner_advance(scanner);
	scanner_advance(scanner);
	extracted = scanner_extract(scanner);
	assert_str_eq("Extracts the characters traversed", "ab", extracted);
	free(extracted);

	assert_section("Extract without advancing");
	extracted = scanner_extract(scanner);
	assert_str_eq("Extracts an empty string if no character was traversed", "", extracted);
	free(extracted);

	assert_section("Skip");
	scanner_advance(scanner);
	scanner_advance(scanner);
	scanner_skip(scanner);
	scanner_advance(scanner);
	scanner_advance(scanner);
	extracted = scanner_extract(scanner);
	assert_str_eq("Skips the characters", "ef", extracted);
	free(extracted);
	
	scanner_destroy(scanner);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Scanner");
	test_suite_add_test(&test_suite, "Basic operations", test_basic_ops);
	test_suite_add_test(&test_suite, "Peek next", test_peek_next);
	test_suite_add_test(&test_suite, "Check", test_check);
	test_suite_add_test(&test_suite, "Advance until", test_advance_until);
	test_suite_add_test(&test_suite, "Advance while", test_advance_while);
	test_suite_add_test(&test_suite, "Match", test_match);
	test_suite_add_test(&test_suite, "Skip and extract", test_skip_extract);
	test_suite_run(&test_suite);
}