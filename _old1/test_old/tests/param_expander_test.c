#include "minishell_test.h"

static void toggle_env(char *param_name, char *param_value)
{
	static char *old_value = NULL;

	if (param_value)
	{
		old_value = getenv(param_name);
		setenv(param_name, param_value, 1);
		return ;
	}

	if (old_value)
	{
		setenv(param_name, old_value, 1);
		old_value = NULL;
	}
	else
		unsetenv(param_name);
}

void test_expansion(char *msg, char *lexeme, char *expansion)
{
	t_token *token = token_construct(T_WORD, ft_strdup(lexeme), NULL);
	expand_params(token);
	assert_eq_str(msg, expansion, token->value);
	token_destruct(token);
}

int	main(void)
{
	static char *param_name = "TEST_PARAM";
	toggle_env(param_name, "ABCD");

	test_expansion("Simple text", "Hello", "Hello");

	test_expansion("Simple expansion", "$TEST_PARAM", "ABCD");
	test_expansion("Simple expansion within word", "abc$TEST_PARAM'a'", "abcABCD'a'");
	test_expansion("Expansion with inexistent param", "abc$TEST_PARAMa", "abc");

	test_expansion("Single quote: text only", "He'll'o", "He'll'o");
	test_expansion("Single quote: no expansion", "'$TEST_PARAM'", "'$TEST_PARAM'");

	test_expansion("Double quote: text only", "\"Hello\"", "\"Hello\"");
	test_expansion("Double quote: with param expansion", "\"Hello $TEST_PARAM there\"", "\"Hello ABCD there\"");

	test_expansion(
		"Mixed test",
		"Hello $TEST_PARAM'$TEST_PARAM\"$TEST_PARAM\"'\"abc$TEST_PARAM\"",
		"Hello ABCD'$TEST_PARAM\"$TEST_PARAM\"'\"abcABCD\"");

	toggle_env(param_name, NULL);
}