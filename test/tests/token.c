#include "libtest_utils.h"
#include "token.h"
#include "libft.h"

static void	test_create_op(void)
{
	t_token	*token;

	token = token_create_op(T_AND);
	assert_int_eq("AND token created", T_AND, token->type);
	assert_str_eq("AND token value set correctly", "&&", token->value);
	token_destroy(token);

	token = token_create_op(T_OR);
	assert_int_eq("OR token created", T_OR, token->type);
	assert_str_eq("OR token value set correctly", "||", token->value);
	token_destroy(token);

	token = token_create_op(T_PIPE);
	assert_int_eq("PIPE token created", T_PIPE, token->type);
	assert_str_eq("PIPE token value set correctly", "|", token->value);
	token_destroy(token);

	token = token_create_op(T_REDIR_IN);
	assert_int_eq("REDIR_IN token created", T_REDIR_IN, token->type);
	assert_str_eq("REDIR_IN token value set correctly", "<", token->value);
	token_destroy(token);

	token = token_create_op(T_REDIR_OUT);
	assert_int_eq("REDIR_OUT token created", T_REDIR_OUT, token->type);
	assert_str_eq("REDIR_OUT token value set correctly", ">", token->value);
	token_destroy(token);

	token = token_create_op(T_REDIR_HEREDOC);
	assert_int_eq("REDIR_HEREDOC token created", T_REDIR_HEREDOC, token->type);
	assert_str_eq("REDIR_HEREDOC token value set correctly", "<<", token->value);
	token_destroy(token);

	token = token_create_op(T_REDIR_APPEND);
	assert_int_eq("REDIR_APPEND token created", T_REDIR_APPEND, token->type);
	assert_str_eq("REDIR_APPEND token value set correctly", ">>", token->value);
	token_destroy(token);

	token = token_create_op(T_PAREN_OPEN);
	assert_int_eq("PAREN_OPEN token created", T_PAREN_OPEN, token->type);
	assert_str_eq("PAREN_OPEN token value set correctly", "(", token->value);
	token_destroy(token);

	token = token_create_op(T_PAREN_CLOSE);
	assert_int_eq("PAREN_CLOSE token created", T_PAREN_CLOSE, token->type);
	assert_str_eq("PAREN_CLOSE token value set correctly", ")", token->value);
	token_destroy(token);

	token = token_create_op(T_EOF);
	assert_int_eq("EOF token created", T_EOF, token->type);
	assert_str_eq("EOF token value set correctly", "newline", token->value);
	token_destroy(token);
}

static void	test_create_word(void)
{
	t_token	*token;

	token = token_create_word(ft_strdup("Word"));
	assert_int_eq("Word token created", T_WORD, token->type);
	assert_str_eq("Word token value set correctly", "Word", token->value);
	token_destroy(token);
}

static void	test_is_redirection_type(void)
{
	t_token	*token;

	token = token_create_op(T_REDIR_IN);
	assert_true("REDIR_IN is a redirection", token_is_redirection_type(token->type));
	token_destroy(token);

	token = token_create_op(T_REDIR_OUT);
	assert_true("REDIR_OUT is a redirection", token_is_redirection_type(token->type));
	token_destroy(token);

	token = token_create_op(T_REDIR_HEREDOC);
	assert_true("REDIR_HEREDOC is a redirection", token_is_redirection_type(token->type));
	token_destroy(token);

	token = token_create_op(T_REDIR_APPEND);
	assert_true("REDIR_APPEND is a redirection", token_is_redirection_type(token->type));
	token_destroy(token);

	token = token_create_op(T_AND);
	assert_true("AND is not a redirection", !token_is_redirection_type(token->type));
	token_destroy(token);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Token");
	test_suite_add_test(&test_suite, "Create operator token", test_create_op);
	test_suite_add_test(&test_suite, "Create word token", test_create_word);
	test_suite_add_test(&test_suite, "Is redirection type", test_is_redirection_type);
	test_suite_run(&test_suite);
}