#include "minishell_test.h"

void	test_token_list_add_op(void)
{
	t_token_list	*token_list;
	t_error			error;

	token_list = NULL;
	error_init(&error);
	token_list_add_op(&token_list, T_GREAT, &error);
	assert_not_null("Creates a token list node", token_list);
	assert_int_eq("Creates and sets op token", token_list->token->type, T_GREAT);
	assert_true("Sets no error", !has_error(&error));
	token_list_clear(&token_list);
}

void	test_token_list_add_word(void)
{
	t_token_list	*token_list;
	t_error			error;

	token_list = NULL;

	error_init(&error);
	token_list_add_word(&token_list, ft_strdup("value"), &error);
	assert_not_null("Creates a token list node", token_list);
	assert_int_eq("Creates and sets token type", token_list->token->type, T_WORD);
	assert_str_eq("Creates and sets token value", "value", token_list->token->value);
	assert_true("Sets no error", !has_error(&error));

	token_list_clear(&token_list);
}


void	test_token_list_del(void)
{
	t_token_list	*token_list;
	t_error			error;

	error_init(&error);
	token_list = NULL;
	token_list_add_word(&token_list, ft_strdup("value"), &error);
	token_list_del(token_list);
	assert_msg("Test with valgrind: No memory leak.");
	error_cleanup(&error);
}

void	test_token_list_clear(void)
{
	t_token_list	*token_list;
	t_error			error;

	token_list = NULL;
	
	assert_section("Clear NULL list");
	token_list_clear(&token_list);
	assert_msg("No error");

	error_init(&error);
	assert_section("Clear list with node");
	token_list_add_word(&token_list, ft_strdup("value"), &error);
	token_list_clear(&token_list);
	assert_msg("Test with valgrind: No memory leak.");
	error_cleanup(&error);
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

	error_init(&error);
	assert_section("Full list");
	token_list_add_op(&token_list, T_GREAT, &error);
	token_list_add_op(&token_list, T_LESS, &error);
	token_list_add_op(&token_list, T_EOF, &error);
	last_node = token_list_last(token_list);
	assert_int_eq("Returns last token", T_EOF, last_node->token->type);
	token_list_clear(&token_list);
	error_cleanup(&error);
}

void	test_token_list_at(void)
{
	t_token_list	*token_list;
	t_error			error;

	token_list = NULL;
	error_init(&error);

	token_list_add_op(&token_list, T_AND_AND, &error);
	token_list_add_op(&token_list, T_GREAT, &error);
	token_list_add_op(&token_list, T_LESS, &error);

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
	error_cleanup(&error);
}

void	test_token_list_insert_after(void)
{
	t_token_list	*original;
	t_token_list	*insertion1;
	t_token_list	*insertion2;
	t_token_list	*insertion3;
	t_token_list	*last_node;
	t_error			error;

	error_init(&error);
	original = NULL;
	insertion1 = NULL;
	insertion2 = NULL;
	insertion3 = NULL;
	token_list_add_op(&insertion1, T_AND_AND, &error);
	token_list_add_op(&insertion1, T_GREAT, &error);
	token_list_add_op(&insertion2, T_GREAT_GREAT, &error);
	token_list_add_op(&insertion2, T_LESS, &error);
	token_list_add_op(&insertion3, T_PIPE, &error);

	assert_section("Insert in empty list");
	token_list_insert_after(&original, insertion1);
	assert_not_null("Creates nodes", original);
	assert_int_eq("Adds first node", T_AND_AND, original->token->type);
	assert_int_eq("Adds second node", T_GREAT, original->next->token->type);

	assert_section("Insert empty list");
	token_list_insert_after(&original, NULL);
	assert_int_eq("Keeps first node", T_AND_AND, original->token->type);
	assert_int_eq("Keeps second node", T_GREAT, original->next->token->type);
	assert_null("Adds no node", original->next->next);

	assert_section("Insert in middle of list");
	token_list_insert_after(&original, insertion2);
	assert_int_eq("Keeps first node", T_AND_AND, original->token->type);
	assert_int_eq("Links first node to second (through next)", T_GREAT_GREAT, original->next->token->type);
	assert_int_eq("Links second node to first (through prev)", T_AND_AND, insertion2->prev->token->type);
	assert_int_eq("Links insertion to following node (through next)",
		T_GREAT, token_list_at(original, 2)->next->token->type);
	assert_int_eq("Links following node to insertion (through prev)",
		T_LESS, token_list_at(original, 3)->prev->token->type);

	assert_section("Insert at the end of the list");
	last_node = token_list_last(original);
	token_list_insert_after(&last_node, insertion3);
	assert_int_eq("Adds node after last node", T_PIPE, token_list_last(original)->token->type);
	assert_int_eq("Links insertion to last node", T_GREAT, token_list_last(original)->prev->token->type);

	token_list_clear(&original);
	error_cleanup(&error);
}

void	test_token_list_remove(void)
{
	t_token_list	*token_list;
	t_error			error;

	token_list = NULL;
	error_init(&error);
	token_list_add_op(&token_list, T_AND_AND, &error);
	token_list_add_op(&token_list, T_GREAT, &error);
	token_list_add_op(&token_list, T_GREAT_GREAT, &error);
	token_list_add_op(&token_list, T_LESS, &error);
	token_list_add_op(&token_list, T_LESS_LESS, &error);
	token_list_add_op(&token_list, T_PIPE, &error);

	assert_section("Remove from NULL");
	token_list_remove(NULL, 1);
	assert_msg("No error");

	assert_section("Remove negative number");
	token_list_remove(&token_list, -1);
	assert_int_eq("No effect", T_GREAT, token_list->next->token->type);

	assert_section("Remove zero");
	token_list_remove(&token_list, 0);
	assert_int_eq("No effect", T_GREAT, token_list->next->token->type);

	assert_section("Remove one at start");
	token_list_remove(&token_list, 1);
	assert_int_eq("Removed the first node", T_GREAT, token_list->token->type);
	assert_null("The new first node has no previous node", token_list->prev);

	assert_section("Remove two in the middle");
	token_list_remove(&token_list->next, 2);
	assert_int_eq("First is connected to old fourth (through next)",
		T_LESS_LESS, token_list->next->token->type);
	assert_int_eq("Old fourth node is connected to first (through prev)",
		T_GREAT, token_list->next->prev->token->type);

	assert_section("Remove one at the end");
	token_list_remove(&token_list->next->next, 1);
	assert_addr_eq("The second node is now the last", token_list_last(token_list), token_list->next);

	assert_section("Remove more than list length");
	token_list_remove(&token_list->next, 20);
	assert_int_eq("Keeps the first node", T_GREAT, token_list->token->type);
	assert_null("Removes the remaining nodes", token_list->next);

	assert_section("Remove entire list");
	token_list_remove(&token_list, 20);
	assert_null("List is empty", token_list);

	token_list_clear(&token_list);
	error_cleanup(&error);
}

void	test_token_list_replace(void)
{
	t_token_list	*original;
	t_token_list	*insertion;
	t_token_list	*insertion2;
	t_error			error;
	t_token_list	*last_node;

	original = NULL;
	insertion = NULL;
	insertion2 = NULL;
	error_init(&error);
	token_list_add_op(&original, T_AND_AND, &error);
	token_list_add_op(&original, T_GREAT, &error);
	token_list_add_op(&original, T_GREAT_GREAT, &error);
	token_list_add_op(&original, T_LESS, &error);
	token_list_add_op(&original, T_LESS_LESS, &error);
	token_list_add_op(&insertion, T_PIPE, &error);
	token_list_add_op(&insertion, T_PIPE_PIPE, &error);
	token_list_add_op(&insertion2, T_PAREN_OPEN, &error);
	token_list_add_op(&insertion2, T_PAREN_CLOSE, &error);

	assert_section("Replace in NULL");
	token_list_replace(NULL, 1, insertion);
	assert_msg("No error");

	assert_section("Replace with NULL at the beginning");
	token_list_replace(&original, 1, NULL);
	assert_int_eq("Removes first element", T_GREAT, original->token->type);
	assert_null("Prev of first element is empty", original->prev);

	assert_section("Replace with token_list in the middle");
	token_list_replace(&(original->next), 2, insertion);
	assert_int_eq("First element correct", T_GREAT, token_list_at(original, 0)->token->type);
	assert_int_eq("Second element correct", T_PIPE, token_list_at(original, 1)->token->type);
	assert_addr_eq("Second element linked to first (with prev)", original, original->next->prev);
	assert_int_eq("Third element correct", T_PIPE_PIPE, token_list_at(original, 2)->token->type);
	assert_int_eq("Fourth element correct", T_LESS_LESS, token_list_at(original, 3)->token->type);
	assert_int_eq("Fourth element linked to third (with prev)",
		T_PIPE_PIPE, token_list_at(original, 3)->prev->token->type);

	assert_section("Replace 10 with NULL at the end");
	last_node = token_list_last(original);
	token_list_replace(&last_node, 10, NULL);
	assert_null("Last element removed", token_list_at(original, 2)->next);

	assert_section("Replace whole list with an insertion");
	token_list_replace(&original, 20, insertion2);
	assert_int_eq("First element correct", T_PAREN_OPEN, original->token->type);
	assert_int_eq("Second element correct", T_PAREN_CLOSE, original->next->token->type);
	assert_null("No third element", original->next->next);

	assert_section("Replace whole list with NULL");
	token_list_replace(&original, 20, NULL);
	assert_null("Empty list", original);

	token_list_clear(&original);
	error_cleanup(&error);
}

int	main(void)
{
	t_test_suite	test_suite;

	test_suite_init(&test_suite, "Token list");

	test_suite_add_test(&test_suite, "Token list add op", test_token_list_add_op);
	test_suite_add_test(&test_suite, "Token list add word", test_token_list_add_word);
	test_suite_add_test(&test_suite, "Token list del", test_token_list_del);
	test_suite_add_test(&test_suite, "Token list clear", test_token_list_clear);
	test_suite_add_test(&test_suite, "Token list last", test_token_list_last);
	test_suite_add_test(&test_suite, "Token list at", test_token_list_at);
	test_suite_add_test(&test_suite, "Token list insert after", test_token_list_insert_after);
	test_suite_add_test(&test_suite, "Token list remove", test_token_list_remove);
	test_suite_add_test(&test_suite, "Token list replace", test_token_list_replace);

	test_suite_run(&test_suite);
}