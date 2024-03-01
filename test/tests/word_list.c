#include "libtest_utils.h"
#include "word_list.h"

#include "libft.h"

static void	test_basic_ops(void)
{
	t_word_list	*words;

	words = NULL;
	word_list_add(&words, "First");
	word_list_add(&words, "Second");
	word_list_add(&words, "Third");
	assert_int_eq("Length is correct", 3, word_list_len(words));
	assert_str_eq("First word is correct", "First", word_list_at(words, 0)->word);
	assert_str_eq("Second word is correct", "Second", word_list_at(words, 1)->word);
	assert_str_eq("Third word is correct", "Third", word_list_at(words, 2)->word);
	assert_str_eq("Last returns the correct word", "Third", word_list_last(words)->word);
	word_list_destroy(words);
	assert_msg("Manual check: No leaks");
}

static void	test_add_sorted(void)
{
	t_word_list	*words;

	words = NULL;
	word_list_add_sorted(&words, "C");
	word_list_add_sorted(&words, "A");
	word_list_add_sorted(&words, "D");
	word_list_add_sorted(&words, "B");
	word_list_add_sorted(&words, "C");

	assert_int_eq("Length is correct", 5, word_list_len(words));
	assert_str_eq("First word is correct", "A", word_list_at(words, 0)->word);
	assert_str_eq("Second word is correct", "B", word_list_at(words, 1)->word);
	assert_str_eq("Third word is correct", "C", word_list_at(words, 2)->word);
	assert_str_eq("Fourth word is correct", "C", word_list_at(words, 3)->word);
	assert_str_eq("Fifth word is correct", "D", word_list_at(words, 4)->word);

	word_list_destroy(words);
}

static void	test_append(void)
{
	t_word_list	*list1;
	t_word_list	*list2;

	list1 = NULL;
	word_list_add(&list1, "One");
	word_list_add(&list1, "Two");
	word_list_add(&list1, "Three");

	list2 = NULL;
	word_list_add(&list2, "Four");
	word_list_add(&list2, "Five");

	assert_section("Setup");
	assert_int_eq("Length of first list is correct", 3, word_list_len(list1));
	assert_int_eq("Length of second list is correct", 2, word_list_len(list2));

	assert_section("Append");
	word_list_append(&list1, list2);
	assert_int_eq("Length of first list has been extended", 5, word_list_len(list1));
	assert_str_eq("Fourth element is correct", "Four", word_list_at(list1, 3)->word);
	assert_str_eq("Fifth element is correct", "Five", word_list_at(list1, 4)->word);

	word_list_destroy(list1);
	assert_msg("Manual check: No leaks");
}

static void	test_to_string(void)
{
	t_word_list	*words;
	char		*converted;

	words = NULL;

	assert_section("Empty list");
	converted = word_list_to_str(words);
	assert_str_eq("Converted string is an empty string", "", converted);
	free(converted);

	assert_section("Non-empty list");
	word_list_add(&words, "AB");
	word_list_add(&words, "CD");
	word_list_add(&words, "EF");
	converted = word_list_to_str(words);
	assert_str_eq("Converted string is correct", "ABCDEF", converted);
	free(converted);

	word_list_destroy(words);
}

static void	test_to_arr(void)
{
	t_word_list	*words;
	char		**converted;

	words = NULL;

	assert_section("Empty list");
	converted = word_list_to_arr(words);
	assert_not_null("Conversion returns a result", converted);
	assert_null("First element is NULL", converted[0]);
	ft_free_2d((void ***) &converted);

	assert_section("Non-empty list");
	word_list_add(&words, "AB");
	word_list_add(&words, "CD");
	word_list_add(&words, "EF");
	converted = word_list_to_arr(words);
	assert_not_null("Conversion returns a result", converted);
	assert_str_eq("First element is correct", "AB", converted[0]);
	assert_str_eq("Second element is correct", "CD", converted[1]);
	assert_str_eq("Third element is correct", "EF", converted[2]);
	assert_null("Fourth element is NULL", converted[3]);
	ft_free_2d((void ***) &converted);

	word_list_destroy(words);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Word list");
	test_suite_add_test(&test_suite, "Basic operations", test_basic_ops);
	test_suite_add_test(&test_suite, "Add sorted", test_add_sorted);
	test_suite_add_test(&test_suite, "Append", test_append);
	test_suite_add_test(&test_suite, "To string", test_to_string);
	test_suite_add_test(&test_suite, "To array", test_to_arr);
	test_suite_run(&test_suite);
}