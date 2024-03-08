#include "libtest_utils.h"
#include "ast.h"

static void	test_basic_ops(void)
{
	t_ast_node	*pipe_node;
	t_ast_node	*cmd_node;
	t_ast_node	*cmd_node2;
	t_ast_node	*subshell_node;

	assert_section("Create command");
	cmd_node = ast_create_cmd(NULL, NULL);
	assert_int_eq("Correct type", AST_CMD, cmd_node->type);
	assert_null("Left is NULL", cmd_node->left);
	assert_null("Right is NULL", cmd_node->right);

	assert_section("Create subshell");
	subshell_node = ast_create_subshell(cmd_node, NULL);
	assert_int_eq("Correct type", AST_SUBSHELL, subshell_node->type);
	assert_addr_eq("Left is cmd node", cmd_node, subshell_node->left);
	assert_null("Right is NULL", subshell_node->right);
	assert_null("Argv is NULL", subshell_node->cmd_argv);

	assert_section("Create binary (pipe)");
	cmd_node2 = ast_create_cmd(NULL, NULL);
	pipe_node = ast_create_binary(AST_PIPE, cmd_node2, subshell_node);
	assert_int_eq("Correct type", AST_PIPE, pipe_node->type);
	assert_addr_eq("Left is cmd node 2", cmd_node2, pipe_node->left);
	assert_addr_eq("Right is subshell node", subshell_node, pipe_node->right);
	assert_null("Argv is NULL", subshell_node->cmd_argv);
	assert_null("Redirections is NULL", subshell_node->redirections);

	ast_destroy(pipe_node);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "AST");
	test_suite_add_test(&test_suite, "Basic ops", test_basic_ops);
	test_suite_run(&test_suite);
}