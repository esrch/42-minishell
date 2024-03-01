#include "libtest_utils.h"
#include "string.h"

static void	test_basic_ops(void)
{
	t_string	*s;

	s = string_create("abc");
	assert_not_null("String was created", s);
	assert_int_eq("String has correct length", 3, string_len(s));
	assert_char_eq("First character correct", 'a', string_at(s, 0));
	assert_char_eq("Second character correct", 'b', string_at(s, 1));
	assert_char_eq("Third character correct", 'c', string_at(s, 2));
	string_destroy(s);
	assert_msg("Manual check: No leaks");
}

static void	test_create(void)
{
	t_string	*s;
	
	assert_section("NULL parameter");
	s = string_create(NULL);
	assert_null("A NULL parameter returns NULL", s);
	assert_section("Long string");
	s = string_create("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	assert_not_null("Can create a long string", s);
	assert_int_eq("String has correct length", 52, string_len(s));
	string_destroy(s);
}

static void	test_cmp(void)
{
	t_string	*s;

	s = string_create("aab");
	assert_int_eq("aab > aaa", 1, string_cmp(s, "aaa"));
	assert_int_eq("aab < aac", -1, string_cmp(s, "aac"));
	assert_int_eq("aab = aab", 0, string_cmp(s, "aab"));
	assert_int_eq("aab < aaba", -1, string_cmp(s, "aaba"));
	assert_int_eq("aab > aa", 1, string_cmp(s, "aa"));
	string_destroy(s);
}

static void	test_ncmp(void)
{
	t_string	*s;

	s = string_create("abcde");
	assert_int_eq("abcde = abcde, n = 5", 0, string_ncmp(s, "abcde", 5));
	assert_int_eq("abcde = abcde, n = 7", 0, string_ncmp(s, "abcde", 7));
	assert_int_eq("abcde = abcdf, n = 5", -1, string_ncmp(s, "abcdf", 7));
	assert_int_eq("abcde = abcdd, n = 5", 1, string_ncmp(s, "abcdd", 7));
	assert_int_eq("abcde > abc, n = 5", 1, string_ncmp(s, "abc", 5));
	assert_int_eq("abcde < abcdefg, n = 7", -1, string_ncmp(s, "abcdefg", 7));
	assert_int_eq("abcde = abcgh, n = 3", 0, string_ncmp(s, "abcgh", 3));
	string_destroy(s);
}	

static void	test_append(void)
{
	t_string	*s;
	char		*converted;

	s = string_create("abc");
	string_append(s, "defghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	assert_int_eq("Correct length", 52, string_len(s));
	converted = string_to_chars(s);
	assert_str_eq("Appended the string",
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
		converted);
	free(converted);
	string_destroy(s);
}

static void	test_append_char(void)
{
	t_string	*s;
	char		*converted;

	s = string_create("abc");
	string_append_char(s, 'd');
	assert_int_eq("Correct length", 4, string_len(s));
	converted = string_to_chars(s);
	assert_str_eq("Appended the character", "abcd", converted);
	free(converted);
	string_destroy(s);
}

static void	test_insert(void)
{
	t_string	*s;
	char		*converted;
	int			return_val;

	s = string_create("");
	assert_int_eq("Initial length of 0", 0, string_len(s));

	assert_section("Insert in empty string");
	string_insert(s, 0, "cd");
	converted = string_to_chars(s);
	assert_str_eq("Added cd at the beginning", "cd", converted);
	free(converted);

	assert_section("Insert at the beginning");
	string_insert(s, 0, "ab");
	converted = string_to_chars(s);
	assert_str_eq("Added ab at the beginning", "abcd", converted);
	free(converted);

	assert_section("Insert at the end");
	string_insert(s, 4, "ef");
	converted = string_to_chars(s);
	assert_str_eq("Added ef at the end", "abcdef", converted);
	free(converted);

	assert_section("Insert in the middle");
	string_insert(s, 4, "gh");
	converted = string_to_chars(s);
	assert_str_eq("Added gh in the middle", "abcdghef", converted);
	free(converted);

	assert_section("Insert out of bounds");
	return_val = string_insert(s, 10, "gh");
	assert_int_eq("Length stays the same", 8, string_len(s));
	assert_int_eq("Returns no error", 0, return_val);
	converted = string_to_chars(s);
	assert_str_eq("String stays the same", "abcdghef", converted);
	free(converted);

	assert_section("Insert NULL in the string");
	string_insert(s, 0, NULL);
	assert_int_eq("Length stays the same", 8, string_len(s));

	string_destroy(s);
}

static void	test_erase(void)
{
	t_string	*s;
	char		*converted;

	s = string_create("abcdefghij");
	assert_int_eq("Initial lenght is 10", 10, string_len(s));

	assert_section("Erase at the end of the string, too many chars");
	string_erase(s, 8, 5);
	assert_int_eq("Erased two characters, not 5", 8, string_len(s));
	converted = string_to_chars(s);
	assert_str_eq("String is correct", "abcdefgh", converted);
	free(converted);

	assert_section("Erase in the middle of the string");
	string_erase(s, 2, 2);
	assert_int_eq("Length is correct", 6, string_len(s));
	converted = string_to_chars(s);
	assert_str_eq("String is correct", "abefgh", converted);
	free(converted);

	assert_section("Erase at the beginning of the string");
	string_erase(s, 0, 2);
	assert_int_eq("Length is correct", 4, string_len(s));
	converted = string_to_chars(s);
	assert_str_eq("String is correct", "efgh", converted);
	free(converted);

	assert_section("Erase out of bounds");
	string_erase(s, 4, 2);
	assert_int_eq("Length did not change", 4, string_len(s));
	converted = string_to_chars(s);
	assert_str_eq("String did not change", "efgh", converted);
	free(converted);

	string_destroy(s);
}

static void	test_replace(void)
{
	t_string	*s;
	char		*converted;
	int			return_val;

	s = string_create("abcdefghij");
	assert_int_eq("Initial lenght is 10", 10, string_len(s));

	assert_section("Replace at the end of the string, too many chars");
	string_replace(s, 8, 5, "klm");
	assert_int_eq("Length is correct", 11, string_len(s));
	converted = string_to_chars(s);
	assert_str_eq("String is correct", "abcdefghklm", converted);
	free(converted);

	assert_section("Replace in the middle of the string");
	return_val = string_replace(s, 2, 2, "123");
	assert_int_eq("No error", 0, return_val);
	assert_int_eq("Length is correct", 12, string_len(s));
	converted = string_to_chars(s);
	assert_str_eq("String is correct", "ab123efghklm", converted);
	free(converted);

	assert_section("Replace at the beginning of the string");
	string_replace(s, 0, 2, "0123");
	assert_int_eq("Length is correct", 14, string_len(s));
	converted = string_to_chars(s);
	assert_str_eq("String is correct", "0123123efghklm", converted);
	free(converted);

	assert_section("Replace out of bounds");
	string_replace(s, 20, 2, "ab");
	assert_int_eq("Length did not change", 14, string_len(s));
	converted = string_to_chars(s);
	assert_str_eq("String did not change", "0123123efghklm", converted);
	free(converted);

	assert_section("Erase with no adding");
	string_replace(s, 0, 4, NULL);
	assert_int_eq("Length is correct", 10, string_len(s));
	converted = string_to_chars(s);
	assert_str_eq("String is correct", "123efghklm", converted);
	free(converted);

	assert_section("Adding with no erasing");
	string_replace(s, 3, 0, "456");
	assert_int_eq("Length is correct", 13, string_len(s));
	converted = string_to_chars(s);
	assert_str_eq("String is correct", "123456efghklm", converted);
	free(converted);

	assert_section("Appending at the end of the string");
	string_replace(s, 13, 5, "no");
	assert_int_eq("Length is correct", 15, string_len(s));
	converted = string_to_chars(s);
	assert_str_eq("String is correct", "123456efghklmno", converted);
	free(converted);

	string_destroy(s);
}

int main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "String");
	test_suite_add_test(&test_suite, "Basic operations", test_basic_ops);
	test_suite_add_test(&test_suite, "Create", test_create);
	test_suite_add_test(&test_suite, "Compare", test_cmp);
	test_suite_add_test(&test_suite, "Compare n", test_ncmp);
	test_suite_add_test(&test_suite, "Append", test_append);
	test_suite_add_test(&test_suite, "Append char", test_append_char);
	test_suite_add_test(&test_suite, "Insert", test_insert);
	test_suite_add_test(&test_suite, "Erase", test_erase);
	test_suite_add_test(&test_suite, "Replace", test_replace);
	test_suite_run(&test_suite);
}