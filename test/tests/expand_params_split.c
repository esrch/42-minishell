#include "libtest_utils.h"
#include "expansion.h"

#include "hash_map.h"
#include "word_list.h"

static void	test_basic_ops(void)
{
	t_word_list	*words;
	t_hash_map	*env;

	env = hash_map_create(NULL);
	hash_map_set(env, "VAR1", "v_value_one_a v_value_one_b");
	hash_map_set(env, "VAR_2", "v_value_two");
	hash_map_set(env, "_VAR3", "v_value_three");
	hash_map_set(env, "4VAR", "v_value_four");

	words = expand_params_split("a$VAR1\"B $VAR_2\"c$_VAR31'$_VAR3'd$_VAR3\"\"$4VAR", env);
	assert_int_eq("Correct number of words", 2, word_list_len(words));
	assert_str_eq("First element correct", "av_value_one_a", word_list_at(words, 0)->word);
	assert_str_eq("Second element correct", "v_value_one_b\"B v_value_two\"c'$_VAR3'dv_value_three\"\"4VAR", word_list_at(words, 1)->word);

	hash_map_destroy(env);
	word_list_destroy(words);
}

static void	test_quotes(void)
{
	t_word_list	*words;
	t_hash_map	*env;

	env = hash_map_create(NULL);
	hash_map_set(env, "VAR1", "ab'c d'ef\" gh\"i");

	words = expand_params_split("01$VAR1'234 '5", env);
	assert_int_eq("Correct number of words", 3, word_list_len(words));
	assert_str_eq("First element correct", "01ab\"'\"c", word_list_at(words, 0)->word);
	assert_str_eq("Second element correct", "d\"'\"ef'\"'", word_list_at(words, 1)->word);
	assert_str_eq("Third element correct", "gh'\"'i'234 '5", word_list_at(words, 2)->word);

	hash_map_destroy(env);
	word_list_destroy(words);
}

static void	test_empty_result(void)
{
	t_word_list	*words;
	t_hash_map	*env;

	env = hash_map_create(NULL);
	words = expand_params_split("$VAR1", env);
	assert_not_null("Result is not null", words);
	assert_int_eq("Contains one element", 1, word_list_len(words));
	assert_str_eq("First element is empty string", "", word_list_at(words, 0)->word);

	hash_map_destroy(env);
	word_list_destroy(words);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Expand params split");
	test_suite_add_test(&test_suite, "Basic operations", test_basic_ops);
	test_suite_add_test(&test_suite, "Quotes in environment variable", test_quotes);
	test_suite_add_test(&test_suite, "Empty result", test_empty_result);
	test_suite_run(&test_suite);
}