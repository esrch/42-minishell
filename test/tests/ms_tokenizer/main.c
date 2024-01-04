#include "minishell_test.h"

void	test_eof_token(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	token_list = ms_tokenize("", &error);
	assert_not_null("Creates a token list", token_list);
	assert_int_eq("Adds EOF token", T_EOF, token_list->token->type);

	token_list_clear(&token_list);
}

void	test_ignore_whitespace(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	assert_section("Whitespace with no tokens");
	token_list = ms_tokenize("     \t  ", &error);
	assert_not_null("Creates a token list", token_list);
	assert_int_eq("Adds EOF token", T_EOF, token_list->token->type);

	token_list_clear(&token_list);

	assert_section("Whitespace with");
	token_list = ms_tokenize("  &&   \t \n ", &error);
	assert_not_null("Creates a token list", token_list);
	assert_int_eq("Adds T_AND_AND token", T_AND_AND, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Adds EOF token", T_EOF, token_list_at(token_list, 1)->token->type);

	token_list_clear(&token_list);
}

void	test_and_and_token(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	token_list = ms_tokenize("&&", &error);
	assert_int_eq("Adds T_AND_AND token", T_AND_AND, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Adds EOF token", T_EOF, token_list_at(token_list, 1)->token->type);
	
	token_list_clear(&token_list);
}

void	test_pipe_token(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	token_list = ms_tokenize("|", &error);
	assert_int_eq("Adds T_PIPE token", T_PIPE, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Adds EOF token", T_EOF, token_list_at(token_list, 1)->token->type);
	
	token_list_clear(&token_list);
}

void	test_pipe_pipe_token(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	assert_section("Single ||");
	token_list = ms_tokenize("||", &error);
	assert_int_eq("Adds T_PIPE_PIPE token",
		T_PIPE_PIPE, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Adds EOF token", T_EOF, token_list_at(token_list, 1)->token->type);

	token_list_clear(&token_list);

	assert_section("Handles ||| correctly");
	token_list = ms_tokenize("|||", &error);
	assert_int_eq("Adds T_PIPE_PIPE token", T_PIPE_PIPE, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Adds T_PIPE token", T_PIPE, token_list_at(token_list, 1)->token->type);
	assert_int_eq("Adds EOF token", T_EOF, token_list_at(token_list, 2)->token->type);
	
	token_list_clear(&token_list);
}

void	test_great_token(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	token_list = ms_tokenize(">", &error);
	assert_int_eq("Adds T_GREAT token", T_GREAT, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Adds EOF token", T_EOF, token_list_at(token_list, 1)->token->type);
	
	token_list_clear(&token_list);
}

void	test_great_great_token(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	assert_section("Single >>");
	token_list = ms_tokenize(">>", &error);
	assert_int_eq("Adds T_GREAT_GREAT token",
		T_GREAT_GREAT, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Adds EOF token", T_EOF, token_list_at(token_list, 1)->token->type);

	token_list_clear(&token_list);

	assert_section("Handles >>> correctly");
	token_list = ms_tokenize(">>>", &error);
	assert_int_eq("Adds T_GREAT_GREAT token", T_GREAT_GREAT, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Adds T_GREAT token", T_GREAT, token_list_at(token_list, 1)->token->type);
	assert_int_eq("Adds EOF token", T_EOF, token_list_at(token_list, 2)->token->type);
	
	token_list_clear(&token_list);
}

void	test_less_token(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	token_list = ms_tokenize("<", &error);
	assert_int_eq("Adds T_LESS token", T_LESS, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Adds EOF token", T_EOF, token_list_at(token_list, 1)->token->type);
	
	token_list_clear(&token_list);
}

void	test_paren_open_token(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	token_list = ms_tokenize("(", &error);
	assert_int_eq("Adds T_PAREN_OPEN token", T_PAREN_OPEN, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Adds EOF token", T_EOF, token_list_at(token_list, 1)->token->type);
	
	token_list_clear(&token_list);
}

void	test_paren_close_token(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	token_list = ms_tokenize(")", &error);
	assert_int_eq("Adds T_PAREN_CLOSE token", T_PAREN_CLOSE, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Adds EOF token", T_EOF, token_list_at(token_list, 1)->token->type);
	
	token_list_clear(&token_list);
}

void	test_less_less_token(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	assert_section("Single <<");
	token_list = ms_tokenize("<<", &error);
	assert_int_eq("Adds T_LESS_LESS token",
		T_LESS_LESS, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Adds EOF token", T_EOF, token_list_at(token_list, 1)->token->type);

	token_list_clear(&token_list);

	assert_section("Handles <<< correctly");
	token_list = ms_tokenize("<<<", &error);
	assert_int_eq("Adds T_LESS_LESS token", T_LESS_LESS, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Adds T_LESS token", T_LESS, token_list_at(token_list, 1)->token->type);
	assert_int_eq("Adds EOF token", T_EOF, token_list_at(token_list, 2)->token->type);
	
	token_list_clear(&token_list);
}

void	test_invalid_metacharacter(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);

	assert_section("Invalid metacharacter: ;");
	token_list = ms_tokenize(";", &error);
	assert_null("Returns a NULL token_list", token_list);
	assert_true("Sets an error", has_error(&error));
	error_cleanup(&error);

	error_init(&error);
	assert_section("Invalid metacharacter: &");
	token_list = ms_tokenize("&", &error);
	assert_null("Returns a NULL token_list", token_list);
	assert_true("Sets an error", has_error(&error));
	error_cleanup(&error);

	error_init(&error);
	assert_section("Invalid metacharacter: &&&");
	token_list = ms_tokenize("&&&", &error);
	assert_null("Returns a NULL token_list", token_list);
	assert_true("Sets an error", has_error(&error));
	error_cleanup(&error);
}

void	test_simple_words(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	assert_section("Single word");
	token_list = ms_tokenize("abc", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "abc", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);

	assert_section("Multiple words");
	token_list = ms_tokenize("abc   cde", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets first T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets first lexeme", "abc", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets first value to NULL", token_list_at(token_list, 0)->token->value);
	assert_int_eq("Sets second T_WORD token type", T_WORD, token_list_at(token_list, 1)->token->type);
	assert_str_eq("Sets second lexeme", "cde", token_list_at(token_list, 1)->token->lexeme);
	assert_null("Sets second value to NULL", token_list_at(token_list, 1)->token->value);
	token_list_clear(&token_list);
}

void	test_simple_double_quotes(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	assert_section("Single word");
	token_list = ms_tokenize("\"abc\"", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "\"abc\"", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);

	assert_section("Spaces in the double quotes");
	token_list = ms_tokenize("\"abc  cde\"", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "\"abc  cde\"", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);

	assert_section("Unclosed double quotes");
	token_list = ms_tokenize("\"abc", &error);
	assert_null("Returns NULL token list", token_list);
	assert_true("Sets error", has_error(&error));
	error_cleanup(&error);

	error_init(&error);
	assert_section("Multiple double quoted words");
	token_list = ms_tokenize("\"abc\" \"cde\"", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets first T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets first lexeme", "\"abc\"", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets first value to NULL", token_list_at(token_list, 0)->token->value);
	assert_int_eq("Sets second T_WORD token type", T_WORD, token_list_at(token_list, 1)->token->type);
	assert_str_eq("Sets second lexeme", "\"cde\"", token_list_at(token_list, 1)->token->lexeme);
	assert_null("Sets second value to NULL", token_list_at(token_list, 1)->token->value);
	token_list_clear(&token_list);
}

void	test_double_quotes_in_word(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	assert_section("Double quote at start");
	token_list = ms_tokenize("\"abc\"def", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "\"abc\"def", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);

	assert_section("Double quote at end");
	token_list = ms_tokenize("abc\"def\"", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "abc\"def\"", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);

	assert_section("Double quote in middle");
	token_list = ms_tokenize("abc\"def\"ghi", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "abc\"def\"ghi", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);

	assert_section("Double quotes in a row");
	token_list = ms_tokenize("abc\"def\"\"ghi\"jkl", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "abc\"def\"\"ghi\"jkl", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);
}

void	test_simple_single_quotes(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	assert_section("Single word");
	token_list = ms_tokenize("'abc'", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "'abc'", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);

	assert_section("Spaces in the single quotes");
	token_list = ms_tokenize("'abc  cde'", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "'abc  cde'", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);

	assert_section("Unclosed single quotes");
	token_list = ms_tokenize("'abc", &error);
	assert_null("Returns NULL token list", token_list);
	assert_true("Sets error", has_error(&error));
	error_cleanup(&error);

	error_init(&error);
	assert_section("Multiple single quoted words");
	token_list = ms_tokenize("'abc' 'cde'", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets first T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets first lexeme", "'abc'", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets first value to NULL", token_list_at(token_list, 0)->token->value);
	assert_int_eq("Sets second T_WORD token type", T_WORD, token_list_at(token_list, 1)->token->type);
	assert_str_eq("Sets second lexeme", "'cde'", token_list_at(token_list, 1)->token->lexeme);
	assert_null("Sets second value to NULL", token_list_at(token_list, 1)->token->value);
	token_list_clear(&token_list);
}

void	test_single_quotes_in_word(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	assert_section("Single quote at start");
	token_list = ms_tokenize("'abc'def", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "'abc'def", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);

	assert_section("Single quote at end");
	token_list = ms_tokenize("abc'def'", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "abc'def'", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);

	assert_section("Single quote in middle");
	token_list = ms_tokenize("abc'def'ghi", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "abc'def'ghi", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);

	assert_section("Single quotes in a row");
	token_list = ms_tokenize("abc'def''ghi'jkl", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "abc'def''ghi'jkl", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);
}

void	test_mixing_quotes(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	assert_section("Single quote inside double quotes");
	token_list = ms_tokenize("\"a'bc\"", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "\"a'bc\"", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);

	assert_section("Double quote inside single quotes");
	token_list = ms_tokenize("'a\"bc'", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "'a\"bc'", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);

	assert_section("All mixed");
	token_list = ms_tokenize("ab'c\"d'\"e'f\"g", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets T_WORD token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets lexeme", "ab'c\"d'\"e'f\"g", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets value to NULL", token_list_at(token_list, 0)->token->value);
	token_list_clear(&token_list);
}

void	test_full_command(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	token_list = ms_tokenize("  ls -l 'test' | cat >> \"output.txt\"", &error);
	assert_not_null("Creates token list", token_list);
	assert_int_eq("Sets first token type", T_WORD, token_list_at(token_list, 0)->token->type);
	assert_str_eq("Sets first lexeme", "ls", token_list_at(token_list, 0)->token->lexeme);
	assert_null("Sets first value to NULL", token_list_at(token_list, 0)->token->value);
	assert_int_eq("Sets second token type", T_WORD, token_list_at(token_list, 1)->token->type);
	assert_str_eq("Sets second lexeme", "-l", token_list_at(token_list, 1)->token->lexeme);
	assert_null("Sets second value to NULL", token_list_at(token_list, 1)->token->value);
	assert_int_eq("Sets third token type", T_WORD, token_list_at(token_list, 2)->token->type);
	assert_str_eq("Sets third lexeme", "'test'", token_list_at(token_list, 2)->token->lexeme);
	assert_null("Sets third value to NULL", token_list_at(token_list, 2)->token->value);
	assert_int_eq("Sets fourth token type", T_PIPE, token_list_at(token_list, 3)->token->type);
	assert_null("Sets fourth lexeme", token_list_at(token_list, 3)->token->lexeme);
	assert_null("Sets fourth value to NULL", token_list_at(token_list, 3)->token->value);
	assert_int_eq("Sets fifth token type", T_WORD, token_list_at(token_list, 4)->token->type);
	assert_str_eq("Sets fifth lexeme", "cat", token_list_at(token_list, 4)->token->lexeme);
	assert_null("Sets fifth value to NULL", token_list_at(token_list, 4)->token->value);
	assert_int_eq("Sets sixth token type", T_GREAT_GREAT, token_list_at(token_list, 5)->token->type);
	assert_null("Sets sixth lexeme", token_list_at(token_list, 5)->token->lexeme);
	assert_null("Sets sixth value to NULL", token_list_at(token_list, 5)->token->value);
	assert_int_eq("Sets seventh token type", T_WORD, token_list_at(token_list, 6)->token->type);
	assert_str_eq("Sets seventh lexeme", "\"output.txt\"", token_list_at(token_list, 6)->token->lexeme);
	assert_null("Sets seventh value to NULL", token_list_at(token_list, 6)->token->value);

	token_list_clear(&token_list);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Minishell tokenizer");

	test_suite_add_test(&test_suite, "EOF token", test_eof_token);
	test_suite_add_test(&test_suite, "Ignores whitespace outside of quotes", test_ignore_whitespace);
	test_suite_add_test(&test_suite, "T_AND_AND token", test_and_and_token);
	test_suite_add_test(&test_suite, "T_PIPE token", test_pipe_token);
	test_suite_add_test(&test_suite, "T_PIPE_PIPE token", test_pipe_pipe_token);
	test_suite_add_test(&test_suite, "T_GREAT token", test_great_token);
	test_suite_add_test(&test_suite, "T_GREAT_GREAT token", test_great_great_token);
	test_suite_add_test(&test_suite, "T_LESS token", test_less_token);
	test_suite_add_test(&test_suite, "T_LESS_LESS token", test_less_less_token);
	test_suite_add_test(&test_suite, "T_PAREN_OPEN token", test_paren_open_token);
	test_suite_add_test(&test_suite, "T_PAREN_CLOSE token", test_paren_close_token);
	test_suite_add_test(&test_suite, "Invalid metacharacter", test_invalid_metacharacter);

	test_suite_add_test(&test_suite, "Simple words", test_simple_words);
	test_suite_add_test(&test_suite, "Simple double quotes", test_simple_double_quotes);
	test_suite_add_test(&test_suite, "Double quotes inside word", test_double_quotes_in_word);
	test_suite_add_test(&test_suite, "Simple single quotes", test_simple_single_quotes);
	test_suite_add_test(&test_suite, "Single quotes inside word", test_single_quotes_in_word);
	test_suite_add_test(&test_suite, "Mixing quotes", test_mixing_quotes);

	test_suite_add_test(&test_suite, "Full command", test_full_command);

	test_suite_run(&test_suite);
}