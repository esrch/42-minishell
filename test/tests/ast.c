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
	pipe_node = ast_create_binary(AST_PIPE, subshell_node, cmd_node2);
	assert_int_eq("Correct type", AST_PIPE, pipe_node->type);
	assert_addr_eq("Left is subshell node", subshell_node, pipe_node->left);
	assert_addr_eq("Right is cmd node 2", cmd_node2, pipe_node->right);
	assert_null("Argv is NULL", subshell_node->cmd_argv);
	assert_null("Redirections is NULL", subshell_node->redirections);

	assert_section("Test at");
	assert_addr_eq("Empty at returns root", pipe_node, ast_at(pipe_node, ""));
	assert_null("Invalid character returns NULL", ast_at(pipe_node, "LLB"));
	assert_addr_eq("L correct", subshell_node, ast_at(pipe_node, "L"));
	assert_addr_eq("R correct", cmd_node2, ast_at(pipe_node, "R"));
	assert_addr_eq("LL correct", cmd_node, ast_at(pipe_node, "LL"));
	assert_null("LLLLLLL is null", ast_at(pipe_node, "LLLLLLL"));

	ast_destroy(pipe_node);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "AST");
	test_suite_add_test(&test_suite, "Basic ops", test_basic_ops);
	test_suite_run(&test_suite);
}