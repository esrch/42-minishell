#include "libtest_utils.h"
#include "parse.h"

#include "heredoc_list.h"
#include "tokenize.h"

static void	test_basic_ops(void)
{
	t_token_list	*tokens;
	t_heredoc_list	*heredocs;
	t_ast_node		*ast;
	t_error			*error;

	heredocs = NULL;
	error = ft_error_create();
	tokens = tokenize("a > b | c << d >> e && f < g | (h | i) | j || k << l", error);
	ast = parse(tokens, &heredocs, error);

	assert_section("Root");
	assert_int_eq("Type correct", AST_OR, ast_at(ast, "")->type);

	assert_section("L");
	assert_int_eq("Type correct", AST_AND, ast_at(ast, "L")->type);

	assert_section("R");
	assert_int_eq("Type correct", AST_CMD, ast_at(ast, "R")->type);
	assert_str_eq("Argv correct", "k", ast_at(ast, "R")->cmd_argv->word);
	assert_int_eq("Redirection type correct", T_REDIR_HEREDOC, ast_at(ast, "R")->redirections->type);
	assert_str_eq("Redirection word correct", "l", ast_at(ast, "R")->redirections->word);

	assert_section("LL");
	assert_int_eq("Type correct", AST_PIPE, ast_at(ast, "LL")->type);

	assert_section("LR");
	assert_int_eq("Type correct", AST_PIPE, ast_at(ast, "LR")->type);

	assert_section("LLL");
	assert_int_eq("Type correct", AST_CMD, ast_at(ast, "LLL")->type);
	assert_str_eq("Argv correct", "a", ast_at(ast, "LLL")->cmd_argv->word);
	assert_int_eq("Redirection type correct", T_REDIR_OUT, ast_at(ast, "LLL")->redirections->type);
	assert_str_eq("Redirection word correct", "b", ast_at(ast, "LLL")->redirections->word);

	assert_section("LLR");
	assert_int_eq("Type correct", AST_CMD, ast_at(ast, "LLR")->type);
	assert_str_eq("Argv correct", "c", ast_at(ast, "LLR")->cmd_argv->word);
	assert_int_eq("First redirection type correct", T_REDIR_HEREDOC, ast_at(ast, "LLR")->redirections->type);
	assert_str_eq("First redirection word correct", "d", ast_at(ast, "LLR")->redirections->word);
	assert_int_eq("Second redirection type correct", T_REDIR_APPEND, ast_at(ast, "LLR")->redirections->next->type);
	assert_str_eq("Second redirection word correct", "e", ast_at(ast, "LLR")->redirections->next->word);

	assert_section("LRL");
	assert_int_eq("Type correct", AST_PIPE, ast_at(ast, "LRL")->type);

	assert_section("LRR");
	assert_int_eq("Type correct", AST_CMD, ast_at(ast, "LRR")->type);
	assert_str_eq("Argv correct", "j", ast_at(ast, "LRR")->cmd_argv->word);

	assert_section("LRLL");
	assert_int_eq("Type correct", AST_CMD, ast_at(ast, "LRLL")->type);
	assert_str_eq("Argv correct", "f", ast_at(ast, "LRLL")->cmd_argv->word);
	assert_int_eq("Redirection type correct", T_REDIR_IN, ast_at(ast, "LRLL")->redirections->type);
	assert_str_eq("Redirection word correct", "g", ast_at(ast, "LRLL")->redirections->word);

	assert_section("LRLR");
	assert_int_eq("Type correct", AST_SUBSHELL, ast_at(ast, "LRLR")->type);

	assert_section("LRLRL");
	assert_int_eq("Type correct", AST_PIPE, ast_at(ast, "LRLRL")->type);

	assert_section("LRLRLL");
	assert_int_eq("Type correct", AST_CMD, ast_at(ast, "LRLRLL")->type);
	assert_str_eq("Argv correct", "h", ast_at(ast, "LRLRLL")->cmd_argv->word);

	assert_section("LRLRLR");
	assert_int_eq("Type correct", AST_CMD, ast_at(ast, "LRLRLR")->type);
	assert_str_eq("Argv correct", "i", ast_at(ast, "LRLRLR")->cmd_argv->word);

	assert_section("Filled the heredoc list");
	assert_addr_eq("First heredoc correct", ast_at(ast, "LLR")->redirections, heredocs->heredoc_node);
	assert_addr_eq("Second heredoc correct", ast_at(ast, "R")->redirections, heredocs->next->heredoc_node);

	ft_error_destroy(error);
	token_list_destroy(tokens);
	ast_destroy(ast);
	heredoc_list_destroy(heredocs);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Parse");
	test_suite_add_test(&test_suite, "Basic operations", test_basic_ops);
	test_suite_run(&test_suite);
}