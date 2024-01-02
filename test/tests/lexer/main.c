#include "minishell_test.h"

void	test_lexer_init(void)
{
	t_lexer	lexer;

	lexer_init(&lexer, "abc");
	assert_str_eq("Source set", "abc", lexer.src);
	assert_int_eq("Start set", 0, lexer.start);
	assert_int_eq("Current set", 0, lexer.current);
}

void	test_lexer_peek(void)
{
	t_lexer	lexer;

	lexer_init(&lexer, "abc");
	assert_char_eq("Peek returns current char", 'a', lexer_peek(&lexer));
}

void	test_lexer_at_end(void)
{
	t_lexer	lexer;

	lexer_init(&lexer, "abc");
	assert_true("Not at end", !lexer_at_end(&lexer));
	lexer.current += 3;
	assert_true("At end", lexer_at_end(&lexer));
}

void	test_lexer_advance(void)
{
	t_lexer	lexer;

	lexer_init(&lexer, "abc");
	assert_char_eq("Advance returns current char", 'a', lexer_advance(&lexer));
	assert_int_eq("Advance moves current forward", 1, lexer.current);
}

void	test_lexer_advance_delim(void)
{
	t_lexer	lexer;
	int		count;

	lexer_init(&lexer, "abc.d,ef");
	count = lexer_advance_delim(&lexer, ".");
	assert_char_eq("Advance delim advances until delimiter (1)", '.', lexer_peek(&lexer));
	assert_int_eq("Advance delim returns number of characters traversed", 3, count);
	count = lexer_advance_delim(&lexer, ",");
	assert_char_eq("Advance delim advances until delimiter (2)", ',', lexer_peek(&lexer));
	count = lexer_advance_delim(&lexer, "!");
	assert_true("Advance delim stops at the end", lexer_at_end(&lexer));
}

static bool	is_space(char c)
{
	return (c == ' ');
}

void	test_lexer_advance_while(void)
{
	t_lexer	lexer;
	int		count;

	lexer_init(&lexer, "   abcdef");
	count = lexer_advance_while(&lexer, is_space);
	assert_char_eq("Advance while advances while predicate is true", 'a', lexer_peek(&lexer));
	assert_int_eq("Advance while returns number of characters traversed (1)", 3, count);
	lexer_init(&lexer, "   ");
	count = lexer_advance_while(&lexer, is_space);
	assert_true("Advance while stops at the end", lexer_at_end(&lexer));
	assert_int_eq("Advance while returns number of characters traversed (2)", 3, count);
}

void	test_lexer_match(void)
{
	t_lexer	lexer;

	lexer_init(&lexer, "abcde");
	
	assert_section("No match");
	assert_false("Match returns false if the string doesn't fully match", lexer_match(&lexer, "ac"));
	assert_int_eq("Match doesn't change current if string doesn't match", 0, lexer.current);

	assert_section("Match start");
	assert_true("Match returns true if the string matches", lexer_match(&lexer, "ab"));
	assert_int_eq("Match doesn't change start if string matches", 0, lexer.start);
	assert_int_eq("Match changes current if string matches", 2, lexer.current);

	assert_section("Match middle");
	lexer.start = 2;
	lexer.current = 2;
	assert_true("Match returns true if the string matches", lexer_match(&lexer, "cd"));
	assert_int_eq("Match doesn't change start if string matches", 2, lexer.start);
	assert_int_eq("Match changes current if string matches", 4, lexer.current);

	assert_section("Match full expected string");
	lexer_init(&lexer, "a");
	assert_false("Match returns false if the string doesn't match", lexer_match(&lexer, "ab"));
	assert_int_eq("Match doesn't change current if string doesn't match", 0, lexer.current);
}

void	test_lexer_extract(void)
{
	t_lexer	lexer;
	char	*extracted;

	lexer_init(&lexer, "abc");
	extracted = lexer_extract(&lexer);
	assert_str_eq("Extract returns an empty string if start == current", "", extracted);
	free(extracted);
	lexer_advance(&lexer);
	lexer_advance(&lexer);
	extracted = lexer_extract(&lexer);
	assert_str_eq("Extract returns the extracted string", "ab", extracted);
	assert_int_eq("Extract doesn't move current", 2, lexer.current);
	assert_int_eq("Extract moves start to current", lexer.current, lexer.start);
	free(extracted);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Lexer");

	test_suite_add_test(&test_suite, "Lexer init", test_lexer_init);
	test_suite_add_test(&test_suite, "Lexer peek", test_lexer_peek);
	test_suite_add_test(&test_suite, "Lexer at end", test_lexer_at_end);
	test_suite_add_test(&test_suite, "Lexer advance", test_lexer_advance);
	test_suite_add_test(&test_suite, "Lexer advance delim", test_lexer_advance_delim);
	test_suite_add_test(&test_suite, "Lexer advance while", test_lexer_advance_while);
	test_suite_add_test(&test_suite, "Lexer match", test_lexer_match);
	test_suite_add_test(&test_suite, "Lexer extract", test_lexer_extract);

	test_suite_run(&test_suite);
}