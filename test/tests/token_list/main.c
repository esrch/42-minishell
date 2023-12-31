#include "../minishell_test.h"

void	test_token_list_add_one(void)
{
	t_token_list	*token_list;
	t_token			*token;

	token_list = NULL;
	token = token_op(T_GREAT);
	token_list_add(&token_list, token);
	assert_eq_int("Token list add one, created the first node", token_list->token->type, T_GREAT);
	assert_eq_true("Token list add one, no next note", token_list->next == NULL);
	token_list_clear(&token_list);
	assert_eq_true("Token list add one, clears list", token_list == NULL);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Token list");

	test_suite_add_test(&test_suite, "Add one", test_token_list_add_one);

	test_suite_run(&test_suite);
}