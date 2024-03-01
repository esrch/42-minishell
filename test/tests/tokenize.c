#include "libtest_utils.h"
#include "tokenize.h"

#include <stdlib.h>

#include "ft_error.h"

static void	test_basic_ops(void)
{
	t_token_list	*tokens;
	t_error			*error;

	error = ft_error_create();
	tokens = tokenize("&& || | < > <<      >>\t( ) word", error);
	assert_int_eq("Length is correct", 11, token_list_len(tokens));
	assert_int_eq("AND token correct", T_AND, token_list_at(tokens, 0)->token->type);
	assert_int_eq("OR token correct", T_OR, token_list_at(tokens, 1)->token->type);
	assert_int_eq("PIPE token correct", T_PIPE, token_list_at(tokens, 2)->token->type);
	assert_int_eq("REDIR_IN token correct", T_REDIR_IN, token_list_at(tokens, 3)->token->type);
	assert_int_eq("REDIR_OUT token correct", T_REDIR_OUT, token_list_at(tokens, 4)->token->type);
	assert_int_eq("REDIR_HEREDOC token correct", T_REDIR_HEREDOC, token_list_at(tokens, 5)->token->type);
	assert_int_eq("REDIR_APPEND token correct", T_REDIR_APPEND, token_list_at(tokens, 6)->token->type);
	assert_int_eq("PAREN_OPEN token correct", T_PAREN_OPEN, token_list_at(tokens, 7)->token->type);
	assert_int_eq("PAREN_CLOSE token correct", T_PAREN_CLOSE, token_list_at(tokens, 8)->token->type);
	assert_int_eq("WORD token type correct", T_WORD, token_list_at(tokens, 9)->token->type);
	assert_str_eq("WORD token value correct", "word", token_list_at(tokens, 9)->token->value);
	assert_int_eq("EOF added at the end", T_EOF, token_list_at(tokens, 10)->token->type);
	token_list_destroy(tokens);
	ft_error_destroy(error);
	assert_msg("Manual check: No leaks");
}

static void	test_greedy(void)
{
	t_error			*error;
	t_token_list	*tokens;

	error = ft_error_create();
	tokens = tokenize("|||", error);
	assert_int_eq("Tokenized OR first", T_OR, token_list_at(tokens, 0)->token->type);
	assert_int_eq("Tokenized PIPE second", T_PIPE, token_list_at(tokens, 1)->token->type);
	token_list_destroy(tokens);
	ft_error_destroy(error);
}

int main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Tokenize");
	test_suite_add_test(&test_suite, "Basic operations", test_basic_ops);
	test_suite_add_test(&test_suite, "Greedy parsing", test_greedy);
	test_suite_run(&test_suite);
}