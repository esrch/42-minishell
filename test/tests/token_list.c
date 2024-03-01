#include "libtest_utils.h"
#include "token_list.h"

#include "token.h"
#include "libft.h"

static void	test_basic_ops(void)
{
	t_token_list	*list;
	t_token			*token;

	list = NULL;
	
	token = token_create_op(T_AND);
	token_list_add(&list, token);
	token_list_add_op(&list, T_OR);
	token_list_add_word(&list, ft_strdup("word"));
	assert_int_eq("Length is correct", 3, token_list_len(list));
	assert_int_eq("First token type correct", T_AND, token_list_at(list, 0)->token->type);
	assert_int_eq("Second token type correct", T_OR, token_list_at(list, 1)->token->type);
	assert_int_eq("Third token type correct", T_WORD, token_list_at(list, 2)->token->type);
	assert_str_eq("Third token value correct", "word", token_list_at(list, 2)->token->value);
	token_list_destroy(list);
	assert_msg("Manual check: No leaks");
}

int main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Token list");
	test_suite_add_test(&test_suite, "Basic operations", test_basic_ops);
	test_suite_run(&test_suite);
}