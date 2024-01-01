#include "../minishell_test.h"

#define TEST_TOKEN_STR(token, token_str, token_type) \
	token->type = token_type; \
	token_str = token_tostring(token); \
	assert_str_eq("Token tostring, " #token_type, #token_type, token_str);

void	test_token_init_cleanup(void)
{
	t_token	token;

	token_init(&token, T_WORD, ft_strdup("lexeme"), ft_strdup("value"));
	assert_int_eq("Token type set", token.type, T_WORD);
	assert_str_eq("Lexeme set", "lexeme", token.lexeme);
	assert_str_eq("Value set", "value", token.value);
	token_cleanup(&token);
}

void	test_token_construct_destruct(void)
{
	t_token	*token;

	token = token_construct(T_WORD, ft_strdup("lexeme"), ft_strdup("value"));
	assert_int_eq("Token construct, token type", token->type, T_WORD);
	assert_str_eq("Token construct, lexeme", "lexeme", token->lexeme);
	assert_str_eq("Token construct, value", "value", token->value);
	token_destruct(token);
}

void	test_token_word(void)
{
	t_token	*token;

	token = token_word(ft_strdup("lexeme"), ft_strdup("value"));
	assert_int_eq("Token word, token type", token->type, T_WORD);
	assert_str_eq("Token word, lexeme", "lexeme", token->lexeme);
	assert_str_eq("Token word, value", "value", token->value);
	token_destruct(token);
}

void	test_token_op(void)
{
	t_token	*token;

	token = token_op(T_GREAT);
	assert_int_eq("Token op, token type", token->type, T_GREAT);
	assert_true("Token op, lexeme", token->lexeme == NULL);
	assert_true("Token op, value", token->value == NULL);
	token_destruct(token);
}

void	test_token_tostring(void)
{
	t_token	*token;
	char	*token_str;

	token = token_op(T_GREAT);
	TEST_TOKEN_STR(token, token_str, T_AND_AND);
	TEST_TOKEN_STR(token, token_str, T_EOF);
	TEST_TOKEN_STR(token, token_str, T_GREAT);
	TEST_TOKEN_STR(token, token_str, T_GREAT_GREAT);
	TEST_TOKEN_STR(token, token_str, T_LESS);
	TEST_TOKEN_STR(token, token_str, T_LESS_LESS);
	TEST_TOKEN_STR(token, token_str, T_PAREN_CLOSE);
	TEST_TOKEN_STR(token, token_str, T_PAREN_OPEN);
	TEST_TOKEN_STR(token, token_str, T_PIPE);
	TEST_TOKEN_STR(token, token_str, T_PIPE_PIPE);
	TEST_TOKEN_STR(token, token_str, T_WORD);
	token_destruct(token);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Token test");

	test_suite_add_test(&test_suite, "Init, cleanup", test_token_init_cleanup);
	test_suite_add_test(&test_suite, "Construct, destruct", test_token_construct_destruct);
	test_suite_add_test(&test_suite, "Token word", test_token_word);
	test_suite_add_test(&test_suite, "Token op", test_token_op);
	test_suite_add_test(&test_suite, "Token tostring", test_token_tostring);

	test_suite_run(&test_suite);
}