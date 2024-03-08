#include "libtest_utils.h"
#include "test_utils.h"
#include "expansion.h"

#include "ft_error.h"
#include "word_list.h"

#define TEST_DIR "expand_wildcard_test"

static void	test_all_files(void)
{
	t_word_list	*matching_files;

	matching_files = expand_wildcard(TEST_DIR, "*");
	assert_int_eq("Number of files correct", 4, word_list_len(matching_files));
	assert_str_eq("First file correct", "abc", word_list_at(matching_files, 0)->word);
	assert_str_eq("Second file correct", "adf", word_list_at(matching_files, 1)->word);
	assert_str_eq("Third file correct", "arc", word_list_at(matching_files, 2)->word);
	assert_str_eq("Fourth file correct", "hbc", word_list_at(matching_files, 3)->word);

	word_list_destroy(matching_files);
}

static void	test_dot_star(void)
{
	t_word_list	*matching_files;

	matching_files = expand_wildcard(TEST_DIR, ".*");
	assert_int_eq("Number of files correct", 2, word_list_len(matching_files));
	assert_str_eq("First file correct", ".", word_list_at(matching_files, 0)->word);
	assert_str_eq("Second file correct", "..", word_list_at(matching_files, 1)->word);

	word_list_destroy(matching_files);
}

static void	test_star_start(void)
{
	t_word_list	*matching_files;

	matching_files = expand_wildcard(TEST_DIR, "a*");
	assert_int_eq("Number of files correct", 3, word_list_len(matching_files));
	assert_str_eq("First file correct", "abc", word_list_at(matching_files, 0)->word);
	assert_str_eq("Second file correct", "adf", word_list_at(matching_files, 1)->word);
	assert_str_eq("Third file correct", "arc", word_list_at(matching_files, 2)->word);

	word_list_destroy(matching_files);
}

static void	test_star_end(void)
{
	t_word_list	*matching_files;

	matching_files = expand_wildcard(TEST_DIR, "*bc");
	assert_int_eq("Number of files correct", 2, word_list_len(matching_files));
	assert_str_eq("First file correct", "abc", word_list_at(matching_files, 0)->word);
	assert_str_eq("Second file correct", "hbc", word_list_at(matching_files, 1)->word);

	word_list_destroy(matching_files);
}

static void	test_star_middle(void)
{
	t_word_list	*matching_files;

	matching_files = expand_wildcard(TEST_DIR, "a*c");
	assert_int_eq("Number of files correct", 2, word_list_len(matching_files));
	assert_str_eq("First file correct", "abc", word_list_at(matching_files, 0)->word);
	assert_str_eq("Second file correct", "arc", word_list_at(matching_files, 1)->word);

	word_list_destroy(matching_files);
}

static void	test_two_stars(void)
{
	t_word_list	*matching_files;

	matching_files = expand_wildcard(TEST_DIR, "*b*");
	assert_int_eq("Number of files correct", 2, word_list_len(matching_files));
	assert_str_eq("First file correct", "abc", word_list_at(matching_files, 0)->word);
	assert_str_eq("Second file correct", "hbc", word_list_at(matching_files, 1)->word);

	word_list_destroy(matching_files);
}

static void	test_no_match(void)
{
	t_word_list	*matching_files;

	matching_files = expand_wildcard(TEST_DIR, "wjk*");
	assert_int_eq("Number of files correct", 1, word_list_len(matching_files));
	assert_str_eq("Returns the input", "wjk*", word_list_at(matching_files, 0)->word);

	word_list_destroy(matching_files);
}

static void	test_quotes(void)
{
	t_word_list	*matching_files;

	assert_section("Star in single quotes doesn't match");
	matching_files = expand_wildcard(TEST_DIR, "a'*'");
	assert_int_eq("Number of files correct", 1, word_list_len(matching_files));
	assert_str_eq("File list returns original string", "a'*'", word_list_at(matching_files, 0)->word);
	word_list_destroy(matching_files);

	assert_section("Star in double quotes doesn't match");
	matching_files = expand_wildcard(TEST_DIR, "a\"*\"");
	assert_int_eq("Number of files correct", 1, word_list_len(matching_files));
	assert_str_eq("File list returns original string", "a\"*\"", word_list_at(matching_files, 0)->word);
	word_list_destroy(matching_files);

	assert_section("Characters in quotes can match");
	matching_files = expand_wildcard(TEST_DIR, "'a'*\"c\"");
	assert_int_eq("Number of files correct", 2, word_list_len(matching_files));
	assert_str_eq("First file correct", "abc", word_list_at(matching_files, 0)->word);
	assert_str_eq("Second file correct", "arc", word_list_at(matching_files, 1)->word);
	word_list_destroy(matching_files);
}

int	main(void)
{
	t_test_suite	test_suite;
	int				setup_dir_result;

	test_suite_init(&test_suite, "Expand wildcard");

	setup_dir_result = setup_test_dir(TEST_DIR, 4, "abc", "adf", "hbc", "arc");
	if (setup_dir_result == 0)
	{
		test_suite_add_test(&test_suite, "All files", &test_all_files);
		test_suite_add_test(&test_suite, "Dot star in pattern", &test_dot_star);
		test_suite_add_test(&test_suite, "Star at the beginning", &test_star_start);
		test_suite_add_test(&test_suite, "Star at the end", &test_star_end);
		test_suite_add_test(&test_suite, "Star in the middle", &test_star_middle);
		test_suite_add_test(&test_suite, "Two stars", &test_two_stars);
		test_suite_add_test(&test_suite, "No match", &test_no_match);
		test_suite_add_test(&test_suite, "Quotes", &test_quotes);
	}

	test_suite_run(&test_suite);

	if (setup_dir_result == 0)
		remove_test_dir(TEST_DIR);
}

#undef TEST_DIR