#include "libtest_utils.h"
#include "token.h"
#include "libft.h"

void	test_token_create_word(void)
{
	t_token	*token;

	token = token_create_word(ft_strdup("value"));
	assert_int_eq("Token type set", T_WORD, token->type);
	assert_str_eq("Token value set", "value", token->value);
	token_destroy(token);
}

void	test_token_create_op(void)
{
	t_token	*token;

	token = token_create_op(T_GREAT);
	assert_int_eq("Token type set", T_GREAT, token->type);
	assert_null("Token value set", token->value);
	token_destroy(token);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Token");

	test_suite_add_test(&test_suite, "Token create word", test_token_create_word);
	test_suite_add_test(&test_suite, "Token create op", test_token_create_op);

	test_suite_run(&test_suite);
}