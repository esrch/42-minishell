#include "libtest_utils.h"
#include "redir_list.h"

#include "libft.h"

static void	test_add_destroy(void)
{
	t_redir_list	*redirections;
	int				return_val;

	redirections = NULL;

	assert_section("In redirection");
	redir_list_add(&redirections, T_REDIR_IN, ft_strdup("in"));
	assert_int_eq("In redirection type set", T_REDIR_IN, redirections->type);
	assert_str_eq("In redirection word set", "in", redirections->word);
	assert_int_eq("In redirection fd set", -1, redirections->fd);

	assert_section("Out redirection");
	redir_list_add(&redirections, T_REDIR_OUT, ft_strdup("out"));
	assert_int_eq("Out redirection type set", T_REDIR_OUT, redir_list_last(redirections)->type);
	assert_str_eq("Out redirection word set", "out", redir_list_last(redirections)->word);
	assert_int_eq("Out redirection fd set", -1, redir_list_last(redirections)->fd);

	assert_section("Heredoc redirection");
	redir_list_add(&redirections, T_REDIR_HEREDOC, ft_strdup("heredoc"));
	assert_int_eq("Heredoc redirection type set", T_REDIR_HEREDOC, redir_list_last(redirections)->type);
	assert_str_eq("Heredoc redirection word set", "heredoc", redir_list_last(redirections)->word);
	assert_int_eq("Heredoc redirection fd set", -1, redir_list_last(redirections)->fd);

	assert_section("Append redirection");
	redir_list_add(&redirections, T_REDIR_APPEND, ft_strdup("append"));
	assert_int_eq("Append redirection type set", T_REDIR_APPEND, redir_list_last(redirections)->type);
	assert_str_eq("Append redirection word set", "append", redir_list_last(redirections)->word);
	assert_int_eq("Append redirection fd set", -1, redir_list_last(redirections)->fd);
	
	assert_section("Append invalid redirection");
	return_val = redir_list_add(&redirections, T_AND, "invalid");
	assert_int_eq("Didn't add invalid redirection (T_AND)", T_REDIR_APPEND, redir_list_last(redirections)->type);
	assert_int_eq("No error", 0, return_val);

	redir_list_destroy(redirections);
	assert_msg("Manual check: No leaks");
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Redirection list");
	test_suite_add_test(&test_suite, "Add and destroy", test_add_destroy);
	test_suite_run(&test_suite);
}