#include "libtest_utils.h"
#include "expansion.h"

static void	test_basic_ops(void)
{
	t_word_list	*words;

	words = expand_split_words("abc def'ghi   jkl'mno\tp\"qrs tuv\"w xyz");
	assert_int_eq("Number of words correct", 4, word_list_len(words));
	assert_str_eq("First word correct", "abc", word_list_at(words, 0)->word);
	assert_str_eq("Second word correct", "def'ghi   jkl'mno", word_list_at(words, 1)->word);
	assert_str_eq("Third word correct", "p\"qrs tuv\"w", word_list_at(words, 2)->word);
	assert_str_eq("Fourth word correct", "xyz", word_list_at(words, 3)->word);

	word_list_destroy(words);
}

static void	test_empty_string(void)
{
	t_word_list	*words;

	words = expand_split_words("");
	assert_not_null("Result is not null", words);
	assert_int_eq("Number of words correct", 1, word_list_len(words));
	assert_str_eq("First word correct", "", word_list_at(words, 0)->word);

	word_list_destroy(words);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Expand: Split words");
	test_suite_add_test(&test_suite, "Basic operations", test_basic_ops);
	test_suite_add_test(&test_suite, "Empty string", test_empty_string);
	test_suite_run(&test_suite);
}