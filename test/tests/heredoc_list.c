#include "libtest_utils.h"
#include "heredoc_list.h"

#include "libft.h"
#include "redir_list.h"

static void	test_basic_ops(void)
{
	t_heredoc_list	*heredocs;
	t_redir_list	*node1;
	t_redir_list	*node2;

	heredocs = NULL;
	node1 = NULL;
	node2 = NULL;
	redir_list_add(&node1, T_REDIR_HEREDOC, ft_strdup("eof1"));
	redir_list_add(&node2, T_REDIR_HEREDOC, ft_strdup("eof2"));

	heredoc_list_add(&heredocs, node1);
	heredoc_list_add(&heredocs, node2);
	assert_addr_eq("Node 1 is correct", node1, heredocs->heredoc_node);
	assert_addr_eq("Node 2 is correct", node2, heredocs->next->heredoc_node);

	redir_list_destroy(node1);
	redir_list_destroy(node2);
	heredoc_list_destroy(heredocs);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Heredoc list");
	test_suite_add_test(&test_suite, "Basic operations", test_basic_ops);
	test_suite_run(&test_suite);
}