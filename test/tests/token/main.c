#include "minishell_test.h"

void	test_token_init_cleanup(void)
{
	t_token	token;

	token_init(&token, T_WORD, ft_strdup("lexeme"), ft_strdup("value"));
	assert_int_eq("Token type set", T_WORD, token.type);
	assert_str_eq("Token lexeme set", "lexeme", token.lexeme);
	assert_str_eq("Token value set", "value", token.value);
	token_cleanup(&token);
}

void	test_token_init_word(void)
{
	t_token	token;

	token_init_word(&token, ft_strdup("lexeme"), ft_strdup("value"));
	assert_int_eq("Token type set", T_WORD, token.type);
	assert_str_eq("Token lexeme set", "lexeme", token.lexeme);
	assert_str_eq("Token value set", "value", token.value);
	token_cleanup(&token);
}

void	test_token_init_op(void)
{
	t_token	token;

	token_init_op(&token, T_GREAT);
	assert_int_eq("Token type set", T_GREAT, token.type);
	assert_null("Token lexeme set", token.lexeme);
	assert_null("Token value set", token.value);
	token_cleanup(&token);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Token");

	test_suite_add_test(&test_suite, "Token init and cleanup", test_token_init_cleanup);
	test_suite_add_test(&test_suite, "Token init word", test_token_init_word);
	test_suite_add_test(&test_suite, "Token init op", test_token_init_op);

	test_suite_run(&test_suite);
}