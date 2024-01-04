#include "minishell_test.h"

void	test_token_list_construct(void)
{
	t_token_list	*token_list;
	t_token			token;

	token_init_op(&token, T_GREAT);
	token_list = token_list_construct(&token, NULL);
	assert_addr_eq("Token set", token_list->token, &token);
	assert_null("Next is null", token_list->next);
	free(token_list);
}

void	test_token_list_add(void)
{
	t_token_list	*token_list;
	t_token			*token1;
	t_token			*token2;
	t_error			error;

	token_list = NULL;
	token1 = malloc(sizeof(*token1));
	token2 = malloc(sizeof(*token2));
	token_init_op(token1, T_GREAT);
	token_init_op(token2, T_LESS);

	error_init(&error);
	assert_section("Empty list");
	token_list_add_token(&token_list, token1, &error);
	assert_not_null("Creates node from NULL token list", token_list);
	assert_addr_eq("Adds the token to the new node", token1, token_list->token);
	assert_false("Sets no error", has_error(&error));

	error_init(&error);
	assert_section("Second node");
	token_list_add_token(&token_list, token2, &error);
	assert_not_null("Creates second node", token_list->next);
	assert_addr_eq("Adds the token to the second node", token2, token_list->next->token);
	assert_false("Sets no error", has_error(&error));

	error_init(&error);
	assert_section("Token is NULL");
	token_list_add_token(&token_list, NULL, &error);
	assert_null("Add fails when no token", token_list->next->next);
	assert_true("Sets the error", has_error(&error));

	free(token1);
	free(token2);
	free(token_list->next);
	free(token_list);
	error_cleanup(&error);
}

void	test_token_list_add_op(void)
{
	t_token_list	*token_list;
	t_error			error;

	token_list = NULL;
	error_init(&error);
	token_list_add_op(&token_list, T_GREAT, &error);
	assert_not_null("Creates a token list node", token_list);
	assert_int_eq("Creates and sets op token", token_list->token->type, T_GREAT);
	assert_false("Sets no error", has_error(&error));
	token_list_clear(&token_list);
}

void	test_token_list_add_word(void)
{
	t_token_list	*token_list;
	t_error			error;

	token_list = NULL;

	error_init(&error);
	token_list_add_word(&token_list, ft_strdup("lexeme"), ft_strdup("value"), &error);
	assert_not_null("Creates a token list node", token_list);
	assert_int_eq("Creates and sets token type", token_list->token->type, T_WORD);
	assert_str_eq("Creates and sets token lexeme", "lexeme", token_list->token->lexeme);
	assert_str_eq("Creates and sets token value", "value", token_list->token->value);
	assert_false("Sets no error", has_error(&error));

	token_list_clear(&token_list);
}


void	test_token_list_del(void)
{
	t_token_list	*token_list;

	token_list = NULL;
	token_list_add_word(&token_list, ft_strdup("lexeme"), ft_strdup("value"), NULL);
	token_list_del(token_list);
	assert_msg("Test with valgrind: No memory leak.");
}

void	test_token_list_clear(void)
{
	t_token_list	*token_list;

	token_list = NULL;
	
	assert_section("Clear NULL list");
	token_list_clear(&token_list);
	assert_msg("No error");

	assert_section("Clear list with node");
	token_list_add_word(&token_list, ft_strdup("lexeme"), ft_strdup("value"), NULL);
	token_list_clear(&token_list);
	assert_msg("Test with valgrind: No memory leak.");
}

void	test_token_list_last(void)
{
	t_token_list	*token_list;
	t_token_list	*last_node;
	t_error			error;

	token_list = NULL;
	
	assert_section("Empty list");
	last_node = token_list_last(token_list);
	assert_null("Last node of empty list is NULL", last_node);

	assert_section("Full list");
	token_list_add_op(&token_list, T_GREAT, &error);
	token_list_add_op(&token_list, T_LESS, &error);
	token_list_add_op(&token_list, T_EOF, &error);
	last_node = token_list_last(token_list);
	assert_int_eq("Returns last token", T_EOF, last_node->token->type);

	token_list_clear(&token_list);
}

void	test_token_list_at(void)
{
	t_token_list	*token_list;

	token_list = NULL;

	token_list_add_op(&token_list, T_AND_AND, NULL);
	token_list_add_op(&token_list, T_GREAT, NULL);
	token_list_add_op(&token_list, T_LESS, NULL);

	assert_section("Index of NULL list");
	assert_null("Returns NULL", token_list_at(NULL, 0));

	assert_section("Negative index");
	assert_null("Returns NULL", token_list_at(token_list, -1));

	assert_section("Correct index");
	assert_int_eq("Returns index 0", T_AND_AND, token_list_at(token_list, 0)->token->type);
	assert_int_eq("Returns index 1", T_GREAT, token_list_at(token_list, 1)->token->type);
	assert_int_eq("Returns index 2", T_LESS, token_list_at(token_list, 2)->token->type);

	assert_section("Index beyond list");
	assert_null("Returns NULL", token_list_at(token_list, 3));

	token_list_clear(&token_list);
}

void	test_token_list_insert(void)
{
	t_token_list	*original;
	t_token_list	*insertion1;
	t_token_list	*insertion2;
	t_token_list	*insertion3;
	t_token_list	*last_node;

	original = NULL;
	insertion1 = NULL;
	insertion2 = NULL;
	insertion3 = NULL;
	token_list_add_op(&insertion1, T_AND_AND, NULL);
	token_list_add_op(&insertion1, T_GREAT, NULL);
	token_list_add_op(&insertion2, T_GREAT_GREAT, NULL);
	token_list_add_op(&insertion2, T_LESS, NULL);
	token_list_add_op(&insertion3, T_PIPE, NULL);

	assert_section("Insert in empty list");
	token_list_insert(&original, insertion1);
	assert_not_null("Creates nodes", original);
	assert_int_eq("Adds first node", T_AND_AND, original->token->type);
	assert_int_eq("Adds second node", T_GREAT, original->next->token->type);

	assert_section("Insert empty list");
	token_list_insert(&original, NULL);
	assert_int_eq("Keeps first node", T_AND_AND, original->token->type);
	assert_int_eq("Keeps second node", T_GREAT, original->next->token->type);
	assert_null("Adds no node", original->next->next);

	assert_section("Insert in middle of list");
	token_list_insert(&original, insertion2);
	assert_int_eq("Keeps first node", T_AND_AND, original->token->type);
	assert_int_eq("Inserts second node", T_GREAT_GREAT, original->next->token->type);
	assert_int_eq("Links to following node", T_GREAT, original->next->next->next->token->type);

	assert_section("Insert at the end of the list");
	last_node = token_list_last(original);
	token_list_insert(&last_node, insertion3);
	assert_int_eq("Adds node after last node", T_PIPE, token_list_last(original)->token->type);

	token_list_clear(&original);
}

void	test_token_list_remove_after(void)
{
	t_token_list	*token_list;

	token_list = NULL;
	token_list_add_op(&token_list, T_AND_AND, NULL);
	token_list_add_op(&token_list, T_GREAT, NULL);
	token_list_add_op(&token_list, T_GREAT_GREAT, NULL);
	token_list_add_op(&token_list, T_LESS, NULL);
	token_list_add_op(&token_list, T_LESS_LESS, NULL);
	token_list_add_op(&token_list, T_PIPE, NULL);

	assert_section("Remove from NULL");
	token_list_remove_after(NULL, 1);
	assert_msg("No error");

	assert_section("Remove negative number");
	token_list_remove_after(token_list, -1);
	assert_int_eq("No effect", T_GREAT, token_list->next->token->type);

	assert_section("Remove zero");
	token_list_remove_after(token_list, 0);
	assert_int_eq("No effect", T_GREAT, token_list->next->token->type);

	assert_section("Remove two");
	token_list_remove_after(token_list, 2);
	assert_int_eq("Removes two nodes", T_LESS, token_list->next->token->type);

	assert_section("Remove more than list length");
	token_list_remove_after(token_list, 20);
	assert_int_eq("Keeps the first node", T_AND_AND, token_list->token->type);
	assert_null("Removes the remaining nodes", token_list->next);

	token_list_clear(&token_list);
}

void	test_token_list_replace_after(void)
{
	t_token_list	*original;
	t_token_list	*insertion;

	original = NULL;
	insertion = NULL;
	token_list_add_op(&original, T_AND_AND, NULL);
	token_list_add_op(&original, T_GREAT, NULL);
	token_list_add_op(&original, T_GREAT_GREAT, NULL);
	token_list_add_op(&original, T_LESS, NULL);
	token_list_add_op(&insertion, T_LESS_LESS, NULL);
	token_list_add_op(&insertion, T_PIPE, NULL);

	assert_section("Replace in NULL");
	token_list_replace_after(NULL, 1, insertion);
	assert_msg("No error");

	assert_section("Replace with NULL");
	token_list_replace_after(original, 1, NULL);
	assert_int_eq("Removes but doesn't insert", T_GREAT_GREAT, original->next->token->type);

	assert_section("Replace with token_list");
	token_list_replace_after(original, 1, insertion);
	assert_int_eq("Removes and inserts", T_LESS_LESS, original->next->token->type);
	assert_int_eq("Connects insertion with rest of list",
		T_LESS, token_list_last(original)->token->type);

	token_list_clear(&original);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Token list");

	test_suite_add_test(&test_suite, "Token list construct", test_token_list_construct);
	test_suite_add_test(&test_suite, "Token list add", test_token_list_add);
	test_suite_add_test(&test_suite, "Token list add op", test_token_list_add_op);
	test_suite_add_test(&test_suite, "Token list add word", test_token_list_add_word);
	test_suite_add_test(&test_suite, "Token list del", test_token_list_del);
	test_suite_add_test(&test_suite, "Token list clear", test_token_list_clear);
	test_suite_add_test(&test_suite, "Token list last", test_token_list_last);
	test_suite_add_test(&test_suite, "Token list at", test_token_list_at);
	test_suite_add_test(&test_suite, "Token list insert", test_token_list_insert);
	test_suite_add_test(&test_suite, "Token list remove after", test_token_list_remove_after);
	test_suite_add_test(&test_suite, "Token list replace", test_token_list_replace_after);

	test_suite_run(&test_suite);
}