#include "libtest_utils.h"
#include "test_utils.h"
#include "expansion.h"

#include "ft_error.h"
#include "hash_map.h"

static void	test_expand_word(void)
{
	t_word_list	*words;
	t_hash_map	*env;
	t_error		*error;
	
	error = ft_error_create();
	env = hash_map_create(NULL);
	hash_map_set(env, "VAR1", "ab* he\"ll\"o");
	hash_map_set(env, "VAR2", "'ab'*");
	hash_map_set(env, "VAR3", "hk");

	words = expand_word("$VAR1 $VAR2 $VAR1' ' $VAR4 *$VAR3", "expand_test", env, error);
	assert_true("No error", !ft_has_error(error));
	if (ft_has_error(error))
		perror("Expand test");
	assert_int_eq("Correct number of words", 8, word_list_len(words));
	assert_str_eq("First word correct", "abc", word_list_at(words, 0)->word);
	assert_str_eq("Second word correct", "abd", word_list_at(words, 1)->word);
	assert_str_eq("Third word correct", "he\"ll\"o", word_list_at(words, 2)->word);
	assert_str_eq("Fourth word correct", "'ab'*", word_list_at(words, 3)->word);
	assert_str_eq("Fifth word correct", "abc", word_list_at(words, 4)->word);
	assert_str_eq("Sixth word correct", "abd", word_list_at(words, 5)->word);
	assert_str_eq("Seventh word correct", "he\"ll\"o ", word_list_at(words, 6)->word);
	assert_str_eq("Eigth word correct", "ghk", word_list_at(words, 7)->word);

	hash_map_destroy(env);
	ft_error_destroy(error);
	word_list_destroy(words);
}

static void	test_expand_list(void)
{
	t_word_list	*original;
	t_word_list	*words;
	t_hash_map	*env;
	t_error		*error;
	
	error = ft_error_create();
	env = hash_map_create(NULL);
	hash_map_set(env, "VAR1", "ab* he\"ll\"o");
	hash_map_set(env, "VAR2", "'ab'*");
	hash_map_set(env, "VAR3", "hk");

	original = NULL;
	word_list_add(&original, "$VAR1");
	word_list_add(&original, "$VAR2");
	word_list_add(&original, "$VAR1' '");
	word_list_add(&original, "$VAR4");
	word_list_add(&original, "*$VAR3");
	words = expand_list(original, "expand_test", env, error);
	assert_true("No error", !ft_has_error(error));
	if (ft_has_error(error))
		perror("Expand test");
	assert_int_eq("Correct number of words", 8, word_list_len(words));
	assert_str_eq("First word correct", "abc", word_list_at(words, 0)->word);
	assert_str_eq("Second word correct", "abd", word_list_at(words, 1)->word);
	assert_str_eq("Third word correct", "he\"ll\"o", word_list_at(words, 2)->word);
	assert_str_eq("Fourth word correct", "'ab'*", word_list_at(words, 3)->word);
	assert_str_eq("Fifth word correct", "abc", word_list_at(words, 4)->word);
	assert_str_eq("Sixth word correct", "abd", word_list_at(words, 5)->word);
	assert_str_eq("Seventh word correct", "he\"ll\"o ", word_list_at(words, 6)->word);
	assert_str_eq("Eigth word correct", "ghk", word_list_at(words, 7)->word);

	hash_map_destroy(env);
	ft_error_destroy(error);
	word_list_destroy(words);
	word_list_destroy(original);
}

int	main(void)
{
	t_test_suite	test_suite;
	int				setup_dir_result;

	test_suite_init(&test_suite, "Expansion");
	setup_dir_result = setup_test_dir("expand_test", 3, "abc", "abd", "ghk");
	if (setup_dir_result == 0)
	{
		test_suite_add_test(&test_suite, "Expansion: Expand word", test_expand_word);
		test_suite_add_test(&test_suite, "Expansion: Expand list", test_expand_list);
	}
	test_suite_run(&test_suite);
	if (setup_dir_result == 0)
		remove_test_dir("expand_test");
}